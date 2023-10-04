#include <Game.h>

namespace snake
{

	/*FRUIT CLASS*/
	Fruit::Fruit()
	{
		fruitVArray = new VertexArray();
		fruitVBuffer = new VertexBuffer(vertexPositions, sizeof(vertexPositions));
		fruitLayout = new VertexBufferLayout();

		fruitLayout->Push<float>(2);

		fruitVArray->Bind();
		fruitVArray->AddBuffer(*fruitVBuffer, *fruitLayout);

		fruitIBuffer = new IndexBuffer(indices, sizeof(indices));

		fruitShader = new Shader("source/Game/Engine/Shader/fruit.shader");

		fruitShader->Bind();
		fruitShader->SetUniform4f("uFruitColor", 0.9f, 0.1f, 0.3f, 1.0f);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	}

	void Fruit::OnUpdate(float deltaTime, GLFWwindow* window)
	{
		model = glm::translate(glm::mat4(1.0f), glm::vec3(fruitPosition[0], fruitPosition[1], 0.0f));
	}


	void Fruit::SetFruitPosition(float x, float y)
	{
		fruitPosition[0] = x;
		fruitPosition[1] = y;
	}

	float* Fruit::GetFruitPosition()
	{
		return fruitPosition;
	}

}