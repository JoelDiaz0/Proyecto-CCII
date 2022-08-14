#pragma once
#include "Platform.h"
class Hell : public Platform
{
public:
	Hell();
	~Hell();
	void initialize() override;
	void generar_bloque_1() override;
	void generar_bloque_2() override;
	void generar_bloque_3() override;
	void generar_bloque_4() override;
private:
	static sf::Texture tex_platform;
};

