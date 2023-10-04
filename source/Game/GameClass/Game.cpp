#include "Game.h"

namespace snake
{
	/*SNAKE GAME CLASS*/
	SnakeGame::SnakeGame(unsigned int height, unsigned int width, GLFWwindow* window) : movesLeft(100), window(window)
	{
		srand(time(NULL));

		snake_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		projection = glm::ortho(0.0f, (float)height, 0.0f, (float)width, -1.0f, 1.0f);
			
		renderer = new Renderer();
		player = new Snake(snake_color);
		fruit = new Fruit();
		grid = new Grid(500);

		player->SetSnakePosition((height / 2.0f), (width / 2.0f));

		float* randomFruit = grid->randomGridPosition();
		fruit->SetFruitPosition(randomFruit[0], randomFruit[1]);

		for (int i = 1; i < 4; i++)
		{
			float lastPos[2] = {(height / 2.0f) + (20.0f * i), (width / 2.0f) + (20.0f * i)};

			Tail* tempTail = new Tail(snake_color);
			tempTail->SetTailPosition(lastPos);

			player->tailVector.push_back(tempTail);
		}

	}

	void SnakeGame::OnUpdate(float deltaTime, GLFWwindow* window)
	{

		/*CHECK FOR INPUTS*/
		float* fruitPos = fruit->GetFruitPosition();
		float* playerPos = player->GetSnakePosition();

		if (fruitPos[0] == playerPos[0] and fruitPos[1] == playerPos[1])
		{
			float* randomFruit = grid->randomGridPosition();
			float newFruitPos[2] = {randomFruit[0], randomFruit[1]};
			std::cout << newFruitPos[0] << ", " << newFruitPos[1] << '\n';

			/* PROBLEMA NO JOGO: A FRUTINHA PODE SPAWNAR NA COBRA
			bool checkingCollision = true;
			bool isColliding = false;
			while (checkingCollision)
			{
				for (int index = 0; index < player->tailVector.size(); index++)
				{
					float* indexTailPos = player->tailVector[index]->GetTailPosition();

					if (indexTailPos[0] == newFruitPos[0] and indexTailPos[1] == newFruitPos[1]) { isColliding = true; }
				}

				if (isColliding)
				{
					std::cout << "Collision FLAG! \n";

					Grid* tempGrid = new Grid(500);

					randomFruit = tempGrid->randomGridPosition();
					newFruitPos[0] = randomFruit[0];
					newFruitPos[0] = randomFruit[1];

					checkingCollision = true;
				}
				else { checkingCollision = false; }
			}
			*/

			fruit->SetFruitPosition(newFruitPos[0], newFruitPos[1]);
			player->AddScore();

			float* lastPos = player->GetSnakeLastPosition();

			Tail* tempTail = new Tail(snake_color);
			tempTail->SetTailPosition(lastPos);

			player->tailVector.push_back(tempTail);
		}
		
		fruit->OnUpdate(deltaTime, window);
		player->OnUpdate(deltaTime, window);
		
	}

	void SnakeGame::OnRender()
	{

		/*RENDER THE GRID AND THE SNAKE*/
		renderer->Clear();
		
		glm::mat4 fruitModel = fruit->GetModel();
		glm::mat4 gridModel = grid->GetModel();
		
		glm::mat4 projectionModelGrid = projection * glm::mat4(1.0f) * gridModel;
		grid->gridShader->Bind();
		grid->gridShader->SetUniformMat4f("uProjectionModel", projectionModelGrid);

		renderer->Draw(grid->gridVArray, grid->gridIBuffer, grid->gridShader);

		glm::mat4 projectionModelFruit = projection * glm::mat4(1.0f) * fruitModel;
		fruit->fruitShader->Bind();
		fruit->fruitShader->SetUniformMat4f("uFruitProjectionModel", projectionModelFruit);

		renderer->Draw(fruit->fruitVArray, fruit->fruitIBuffer, fruit->fruitShader);
		
		player->OnRender(renderer, projection);	
	}

	void SnakeGame::ImGuiRender()
	{
		
	}
}