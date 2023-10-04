#include <Game.h>

namespace snake
{

	Grid::Grid(unsigned int size)
	{
		float gridSize = (float)size;

		for (int j = 0; j < 8; j++)
		{
			if (vertexPositions[j] > 0)
				vertexPositions[j] = (gridSize / 2.0f);
			else
				vertexPositions[j] = -(gridSize / 2.0f);
		}

		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					gridCoords[i][j][0] = (((float)j) * 20.0f) + 60.0f;
					gridCoords[i][j][1] = (((float)i) * 20.0f) + 60.0f;
				}
			}
		}

		gridVArray = new VertexArray();
		gridVBuffer = new VertexBuffer(vertexPositions, sizeof(vertexPositions));
		gridLayout = new VertexBufferLayout();

		gridLayout->Push<float>(2);

		gridVArray->Bind();
		gridVArray->AddBuffer(*gridVBuffer, *gridLayout);

		gridIBuffer = new IndexBuffer(indices, sizeof(indices));

		gridShader = new Shader("source/Game/Engine/Shader/grid.shader");

		gridShader->Bind();
		gridShader->SetUniform4f("uColor", 0.0f, 0.0f, 0.0f, 1.0f);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(300, 300, 0.0f));
	}

	void Grid::OnUpdate(float deltaTime, GLFWwindow* window)
	{ }

	float* Grid::randomGridPosition()
	{
		int i = (rand() % 25);
		int j = (rand() % 25);


		float x = gridCoords[i][j][0];
		float y = gridCoords[i][j][1];

		float arr[2] = { x, y };

		return arr;
	}
}