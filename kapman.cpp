#include "kapman.h"

const int Kapman::SPEED = 1;

Kapman::Kapman() : m_x(0), m_y(0), m_xSpeed(0), m_ySpeed(0) {

}

Kapman::~Kapman() {

}

void Kapman::goUp() {
	m_xSpeed = 0;
	m_ySpeed = -SPEED;
}

void Kapman::goDown() {
	m_xSpeed = 0;
	m_ySpeed = SPEED;
}

void Kapman::goRight() {
	m_xSpeed = SPEED;
	m_ySpeed = 0;
}

void Kapman::goLeft() {
	m_xSpeed = -SPEED;
	m_ySpeed = 0;
}

void Kapman::move() {
	m_x += m_xSpeed;
	m_y += m_ySpeed;
	emit(moved(m_x, m_y));
}

int Kapman::getX() const {
	return m_x;
}

int Kapman::getY() const {
	return m_y;
}
