#include <Game.h>


namespace snake
{

	/*SNAKE CLASS*/
	Tail::Tail(glm::vec4 snake_color) : color(snake_color), initialPos(true)
	{
		tailVArray = new VertexArray();
		tailVBuffer = new VertexBuffer(tailVertexPositions, sizeof(tailVertexPositions));
		tailLayout = new VertexBufferLayout();

		tailLayout->Push<float>(2);

		tailVArray->Bind();
		tailVArray->AddBuffer(*tailVBuffer, *tailLayout);

		tailIBuffer = new IndexBuffer(indices, sizeof(indices));

		tailShader = new Shader("source/Game/Engine/Shader/snake.shader");

		tailShader->Bind();
		tailShader->SetUniform4f("uColor", color[0], color[1], color[2], color[3]);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	}

	void Tail::OnUpdate(float deltaTime, GLFWwindow* window)
	{

		model = glm::translate(glm::mat4(1.0f), glm::vec3(tailPosition[0], tailPosition[1], 0.0f));

	}

	void Tail::OnRender(Renderer* renderer, glm::mat4 projection)
	{
		glm::mat4 projectionModel = projection * glm::mat4(1.0f) * model;
		tailShader->Bind();
		tailShader->SetUniformMat4f("uProjectionModel", projectionModel);

		renderer->Draw(tailVArray, tailIBuffer, tailShader);
	}

	void Tail::SetTailPosition(float* position)
	{
		if (initialPos)
		{
			tailPosition[0] = position[0];
			tailPosition[1] = position[1];
			initialPosition[0] = position[0];
			initialPosition[1] = position[1];

			initialPos = false;
		}
		else
		{
			tailPosition[0] = position[0];
			tailPosition[1] = position[1];
		}
	}

	void Tail::SetTailLastPosition(float* position)
	{
		tailLastPosition[0] = position[0];
		tailLastPosition[1] = position[1];
	}

	float* Tail::GetTailPosition()
	{
		return tailPosition;
	}

	float* Tail::GetTailLastPosition()
	{
		return tailLastPosition;
	}

}