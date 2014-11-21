#ifndef ENTITY_H
#define ENTITY_H

#include <utility>

class Entity
{
	public:
		Entity(std::pair<unsigned,unsigned> param) : position_{param}, alive_{true} {};
	
		void render();
		
		virtual void update() = 0;
		virtual void collision(Entity*) = 0;
		
		std::pair<unsigned, unsigned> get_position();
		bool get_alive();
		void set_alive(bool);
		
	private:
		std::pair<unsigned,unsigned> position_;
		bool alive_;
};


/*
/	Live Objects 
*/
/*
class Live_Object : public Entity
{
	public:
		virtual void read_input() = 0;
	private:
		unsigned speed_;
		float facing_angle_;
};

class Player : public Live_Object
{
	public:
		void update();
		void read_input();
		void collision(Entity*);
};

class NPC : public Live_Object
{
	public:
		void update();
		void read_input();
		void collision(Entity*);
};

class Projectile : public Live_Object
{
	public:
		void update();
		void read_input();
		void collision(Entity*);
};*/

/*
/	Static Objects	
*/

class Wall : public Entity
{
	public:
		Wall(std::pair<unsigned,unsigned> param) : Entity{param} {};
		
		void update();
		void collision(Entity*);
};

class Spawner : public Entity
{
	public:
		Spawner(std::pair<unsigned,unsigned> param) : Entity{param} {};
		
		void update();
		void collision(Entity*);
};

#endif