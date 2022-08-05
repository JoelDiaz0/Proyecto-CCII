#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Excepcion : public exception
{
public:
	const char* what();
};