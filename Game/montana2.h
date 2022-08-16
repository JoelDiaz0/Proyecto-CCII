#include <iostream>
#include "Platform.h"
class montana2 : public Platform
{
public:
	montana2();
	~montana2();
	void initialize() override;
	void generar_bloque_1() override;
	void generar_bloque_2() override;
	void generar_bloque_3() override;
	void generar_bloque_4() override;
private:
	static sf::Texture tex_platform;
};


