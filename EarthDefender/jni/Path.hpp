#ifndef PATH_HPP_
#define PATH_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include "Textures.hpp"
#include "Vec3Enemy.hpp"
#include "Positionable.hpp"
#include "Textureable.hpp"

class Path : public sf::Drawable, public Positionable, public Textureable{
public:
	enum PathType{
		NS=1,
		WE=2,
		SE=3,
		SW=4,
		NW=5,
		NE=6,

		SN=7,
		EW=8,
		ES=9,
		WS=10,
		WN=11,
		EN=12
	};

	enum PathDir{
		goN,
		goS,
		goW,
		goE
	};

private:
	std::vector<Vec3Enemy> enemypos;
	std::vector<PathDir> vstep;
	std::vector<sf::Vector2i> veci;
	std::vector<PathType> vtype;
	std::vector<PathType> vtypeprec;

	sf::Vector2i start;
	sf::Vector2i lastPos;
	sf::Vector2i tileAfterStart;
	sf::VertexArray va;
	sf::Vector2i lastPathPos;
	int iterator;
	size_t iter;
	float pathLength;
	sf::FloatRect lastFr;

	void nextVec2i(sf::Vector2i &p, PathDir now, PathDir last) const;//metoda uzupełniająca wektor p wartościami x oraz y na jakich znajduje się droga na mapie.
public:
	Path():
		iterator(0),
		iter(0),
		pathLength(0.f)
	{
		va.setPrimitiveType(sf::Triangles);

	}
	virtual ~Path(){

	}
	void initVec3Enemy();// metoda inicjalizująca kontener danych enemypos.
	inline void setVstep(std::vector<PathDir> &v){vstep=v;}//metoda ustawiająca wektor kierunków na podany w parametrze.
	inline void setStart(sf::Vector2i s){start=s;}// metoda ustawiająca początek drogi na wygrane pole na mapie.
	inline sf::Vector2i getStart(){return start;}// metoda zwracająca początek drogi.
	inline std::vector<Path::PathDir>* getPath(){return &vstep;}// metoda zwracająca wektor kierunków jakimi idzie droga.
	inline sf::Vector2i getTileAfterStart(){ return tileAfterStart;}// metoda zwracająca drugie miejsce na mapie.
	void string2path(std::string s);// metoda zmieniająca string na drogę w wektorze vstep.
	void draw(sf::RenderTarget &target, sf::RenderStates states)const;// metoda draw wymagana przy implementacji sf::Drawable(rysowanie obiektów).
	void updateVa();// odświerzenie drogi w przypadku jakiś zmian.
	void updateVaForce();
	bool isCollide(sf::Vector2i p) const;
	inline sf::Vector2i getLastPathPos() const{return lastPathPos;}// metoda zwracająca ostatnią współrzędną x oraz y drogi potrzebną do ustawienia tam bazy.
	const std::vector<sf::Vector2i> &getAsVector()const;// metoda zwracająca referencję na wektor veci.
	PathType getTypeAt(sf::Vector2i)const;// metoda zwracająca typ kierunku na danej kafelce (enum PathType od 1 - 6).
	PathType getTypeAtPrec(sf::Vector2i)const;// metoda zwracająca typ kierunku na danej kafelce (enum PathType od 1 - 12).
	std::vector<Vec3Enemy> &Vec3EnemyPos(){return enemypos;}// metoda zwracająca wektor punktów po których może poruszać się przeciwnik.
};

#endif /* PATH_HPP_ */
