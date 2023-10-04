#ifndef CURRENT_GAME_H
#define CURRENT_GAME_H

#include <engine.h>

namespace snake
{
	class Game
	{
	public:
		Game() {};
		~Game() {};

		virtual void OnUpdate(float deltaTime, GLFWwindow* window) {}
		virtual void OnRender(Renderer* renderer, glm::mat4 projection) {}
		virtual void ImGuiRender() {}
	};


#ifndef TAIL_H
#define TAIL_H
	class Tail : public Game
	{
	public:
		Tail(glm::vec4 snake_color);

		inline glm::mat4 GetModel() { return model; }

		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender(Renderer* renderer, glm::mat4 projection) override;

		Shader* tailShader;
		VertexArray* tailVArray;
		IndexBuffer* tailIBuffer;
		inline VertexBuffer GetVB() { return *tailVBuffer; }
		inline VertexBufferLayout GetLayout() { return *tailLayout; }

		void SetTailPosition(float* position);
		void SetTailLastPosition(float* position);

		float* GetTailPosition();
		float* GetTailLastPosition();
	private:
		glm::mat4 model;
		glm::vec4 color;


		/*DEFINE MESH*/
		VertexBuffer* tailVBuffer;
		VertexBufferLayout* tailLayout;

		float direction[2] = { 0.0f, -1.0f };
		float initialPosition[2] = { 0.0f, 0.0f };
		float tailLastPosition[2] = { 0.0f, 0.0f };
		bool initialPos;

		float tailPosition[2] = { 0.0f, 0.0f };
		float tailVertexPositions[8] =
		{
			-10.0f,-10.0f,
			-10.0f, 10.0f,
			 10.0f,-10.0f,
			 10.0f, 10.0f
		};

		unsigned int indices[6] =
		{
			0, 1, 2,
			1, 2, 3
		};
	};


#endif


#ifndef SNAKE_H
#define SNAKE_H
	class Snake : public Game
	{
	public:
		Snake(glm::vec4 snake_color);

		inline glm::mat4 GetModel() { return model; }

		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender(Renderer* renderer, glm::mat4 projection) override;

		Shader* snakeShader;
		VertexArray* snakeVArray;
		IndexBuffer* snakeIBuffer;
		bool snakeAlive = true;
		inline VertexBuffer GetVB()			  { return *snakeVBuffer;}
		inline VertexBufferLayout GetLayout() { return *snakeLayout; }

		void SetSnakePosition(float x, float y);
		float* GetSnakePosition();
		float* GetSnakeLastPosition();

		inline void AddScore() { score += 1; }
		inline void ResetScore() { score = 0; }
		inline unsigned int GetScore() { return score; }

		std::vector<Tail*> tailVector;
	private:
		glm::mat4 model;
		glm::vec4 color;


		/*DEFINE MESH*/
		VertexBuffer* snakeVBuffer;
		VertexBufferLayout* snakeLayout;

		unsigned int score;

		unsigned int frameCount;
		bool pressed;

		const unsigned int SPEED = 16;
		float direction[2] = { 0.0f, -1.0f };
		float initialPosition[2] = { 0.0f, 0.0f };
		float snakeLastPosition[2] = { 0.0f, 0.0f };
		bool initialPos;

		float snakePosition[2]   = { 0.0f, 0.0f };
		float snakeVertexPositions[8] =
		{
			-10.0f,-10.0f,
			-10.0f, 10.0f,
			 10.0f,-10.0f,
			 10.0f, 10.0f
		};

		unsigned int indices[6] =
		{
			0, 1, 2,
			1, 2, 3
		};
	};

#endif



#ifndef FRUIT_H
#define	FRUIT_H
	class Fruit : public Game
	{
	public:
		Fruit();

		inline glm::mat4 GetModel() { return model; }

		void OnUpdate(float deltaTime, GLFWwindow* window) override;

		Shader* fruitShader;
		VertexArray* fruitVArray;
		IndexBuffer* fruitIBuffer;
		inline VertexBuffer GetVB() { return *fruitVBuffer; }
		inline VertexBufferLayout GetLayout() { return *fruitLayout; }

		void SetFruitPosition(float x, float y);
		float* GetFruitPosition();

	private:
		glm::mat4 model;

		/*DEFINE MESH*/
		VertexBuffer* fruitVBuffer;
		VertexBufferLayout* fruitLayout;

		float fruitPosition[2] = { 0.0f, 0.0f };
		float vertexPositions[8] =
		{
			-10.0f,-10.0f,
			-10.0f, 10.0f,
			 10.0f,-10.0f,
			 10.0f, 10.0f,
		};

		unsigned int indices[6] =
		{
			0, 1, 2,
			1, 2, 3
		};
	};
#endif

#ifndef GRID_H
#define GRID_H
	class Grid : public Game
	{
	public:
		Grid(unsigned int size);

		void OnUpdate(float deltaTime, GLFWwindow* window) override;

		inline glm::mat4 GetModel() { return model; }

		Shader* gridShader;
		VertexArray* gridVArray;
		IndexBuffer* gridIBuffer;
		inline VertexBuffer GetVB() { return *gridVBuffer; }
		inline VertexBufferLayout GetLayout() { return *gridLayout; }

		float* randomGridPosition();

	private:
		glm::mat4 model;

		/*DEFINE MESH*/
		VertexBuffer* gridVBuffer;
		VertexBufferLayout* gridLayout;

		float gridCoords[25][25][2];
		float vertexPositions[8] =
		{
			-10.0f,-10.0f,
			-10.0f, 10.0f,
			 10.0f,-10.0f,
			 10.0f, 10.0f,
		};

		unsigned int indices[6] =
		{
			0, 1, 2,
			1, 2, 3
		};
	};
#endif

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
	class SnakeGame : public Game
	{
	public:
		SnakeGame(unsigned int height, unsigned int width, GLFWwindow* window);

		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender();
		void ImGuiRender() override;
		inline bool IsPlayerAlive() { return player->snakeAlive; }

	private:
		/*Camera view*/
		glm::mat4 projection;
		GLFWwindow* window;

		Renderer* renderer;
		Fruit* fruit;
		Snake* player;
		Grid* grid;

		std::vector<Snake*> tail;

		glm::vec4 snake_color;

		unsigned int movesLeft;
	};
#endif
}


#endif