//////////////////////////////
//	Live Objects 
//////////////////////////////

class LiveObject : public Entity
{
	public:
		LiveObject(int posX, int posY, unsigned width, unsigned height, double speed, double acceleration) 
			: targetPosX_{posX}, targetPosY_{posY}, speed_{speed}, acceleration_{acceleration}, alive_{true}, Entity{posX, posY, width, height} {}
		
		int getTargetX() { return targetPosX_; }
		int getTargetY() { return targetPosY_; }
		
		bool getAlive();
		void setAlive(bool);
		
	protected:
		bool entityCollision(Entity*);
		bool entityCollisionCheck(Entity*);
		bool boundryBoxCollision(const Map&);
		bool boundryBoxCollisionCheck(const Map&);
	
		double moveCapacityX_{0}, moveCapacityY_{0};
		double acceleration_;
		double targetPosX_, targetPosY_;
		double speed_;
		
		bool alive_;
};