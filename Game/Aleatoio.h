#include <random>
#include <iostream>
template<typename T>
class Aleatorio
{
public:
	Aleatorio() {}
	inline T get_numero(T lim_inf, T lim_sup);
	~Aleatorio() {}
private:
	T val;
};

template<typename T>
T Aleatorio<T>::get_numero(T lim_inf, T lim_sup)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<T> dist(lim_inf, lim_sup);
	val = dist(mt);
	return val;
}

template<>
class  Aleatorio<float> {
public:
	Aleatorio() {}
	~Aleatorio() {}
	inline float get_numero(float lim_inf, float lim_sup);

};

inline float Aleatorio<float>::get_numero(float lim_inf, float lim_sup)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(lim_inf, lim_sup);
	float val = dist(mt);
	return val;

}
