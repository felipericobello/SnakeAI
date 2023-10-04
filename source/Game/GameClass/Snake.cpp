#include <Game.h>

namespace snake
{

	/*SNAKE CLASS*/
	Snake::Snake(glm::vec4 snake_color) : color(snake_color), frameCount(0), pressed(false), initialPos(true), score(0)
	{
		snakeVArray = new VertexArray();
		snakeVBuffer = new VertexBuffer(snakeVertexPositions, sizeof(snakeVertexPositions));
		snakeLayout = new VertexBufferLayout();

		snakeLayout->Push<float>(2);

		snakeVArray->Bind();
		snakeVArray->AddBuffer(*snakeVBuffer, *snakeLayout);

		snakeIBuffer = new IndexBuffer(indices, sizeof(indices));

		snakeShader = new Shader("source/Game/Engine/Shader/snake.shader");

		snakeShader->Bind();
		snakeShader->SetUniform4f("uColor", color[0], color[1], color[2], color[3]);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	}

	void Snake::OnUpdate(float deltaTime, GLFWwindow* window)
	{
		/*CHECK FOR INPUTS*/
		/*if snake is on grid-square center:*/
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS and !direction[1] and pressed == false)
		{
			direction[0] = 0;
			direction[1] = 1.0f;
			pressed = true;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS and !direction[1] and pressed == false)
		{
			direction[0] = 0.0f;
			direction[1] = -1.0f;
			pressed = true;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS and !direction[0] and pressed == false)
		{
			direction[0] = 1.0f;
			direction[1] = 0.0f;
			pressed = true;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS and !direction[0] and pressed == false)
		{
			direction[0] = -1.0f;
			direction[1] = 0.0f;
			pressed = true;
		}

		frameCount += 1;

		if (frameCount == SPEED)
		{
			snakeLastPosition[0] = snakePosition[0];
			snakeLastPosition[1] = snakePosition[1];

			snakePosition[0] += (20.0f * direction[0]); //SIZEOF SNAKE HEAD * DIRECTION
			snakePosition[1] += (20.0f * direction[1]);

			pressed = false;
			frameCount = 0;

			if (!tailVector.empty())
			{
				tailVector[0]->SetTailLastPosition(tailVector[0]->GetTailPosition());
				tailVector[0]->SetTailPosition(snakeLastPosition);
				for (int i = 1; i < tailVector.size(); i++)
				{
					tailVector[i]->SetTailLastPosition(tailVector[i]->GetTailPosition());
					tailVector[i]->SetTailPosition(tailVector[i - 1]->GetTailLastPosition());
					if (snakePosition[0] == tailVector[i]->GetTailPosition()[0] and snakePosition[1] == tailVector[i]->GetTailPosition()[1])
					{
						SetSnakePosition(initialPosition[0], initialPosition[1]);
						ResetScore();
						tailVector.clear();
						snakeAlive = false;
					}
				}
			}
		}

		if (snakePosition[0] == 40 or snakePosition[0] == 560 or snakePosition[1] == 40 or snakePosition[1] == 560) // or movesLeft == 0
		{
			SetSnakePosition(initialPosition[0], initialPosition[1]);
			ResetScore();
			tailVector.clear();
			snakeAlive = false;
		}

		if (!tailVector.empty())
		{
			for (int i = 0; i < tailVector.size(); i++)
			{
				tailVector[i]->OnUpdate(deltaTime, window);
			}
		}


		model = glm::translate(glm::mat4(1.0f), glm::vec3(snakePosition[0], snakePosition[1], 0.0f));
	}

	void Snake::OnRender(Renderer* renderer, glm::mat4 projection)
	{
		glm::mat4 projectionModelPlayer = projection * glm::mat4(1.0f) * model;
		snakeShader->Bind();
		snakeShader->SetUniformMat4f("uProjectionModel", projectionModelPlayer);

		renderer->Draw(snakeVArray, snakeIBuffer, snakeShader);

		for (int i = 0; i < tailVector.size(); i++)
		{
			tailVector[i]->OnRender(renderer, projection);
		}
	}

	void Snake::SetSnakePosition(float x, float y)
	{
		if (initialPos)
		{
			snakePosition[0] = x;
			snakePosition[1] = y;
			initialPosition[0] = x;
			initialPosition[1] = y;

			initialPos = false;
		}
		else
		{
			snakePosition[0] = x;
			snakePosition[1] = y;
		}
	}

	float* Snake::GetSnakePosition()
	{
		return snakePosition;
	}

	float* Snake::GetSnakeLastPosition()
	{
		return snakeLastPosition;
	}
}