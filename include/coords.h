class CH3D{
	public:
		float x,y,z;
		float w;
		void update(float x,float y,float z);
	protected:
		CH3D(void);
		CH3D(float x,float y,float z,float w);
		CH3D(const CH3D &ch);

		~CH3D(void);
};

class Pos3D:public CH3D{
	public :
		Pos3D();
		Pos3D(float x, float y, float z);
		Pos3D(const Pos3D &p);
		~Pos3D();

		Pos3D operator+(const Pos3D);
		Pos3D operator-(const Pos3D);
			
};

class Dir3D:public CH3D{
	public :
		Dir3D();
		Dir3D(float x, float y, float z);
		Dir3D(Dir3D &d);
		Dir3D(const Pos3D &p1, const Pos3D &p2);
		Dir3D(float x1, float y1, float z1,float x2, float y2, float z2);
		~Dir3D();
		float operator*(const Dir3D &d);
		Dir3D operator^(const Dir3D &d);
};