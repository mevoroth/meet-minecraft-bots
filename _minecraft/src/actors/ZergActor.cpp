#include "ZergActor.hpp"

#include <cmath>

#include "ActorsRepository.hpp"

using namespace DatNS;

ZergActor::ZergActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw)
	: Actor(pos, speed, fw)
{
	vector<float>& v = vertices;
	vector<float>& c = colors;
	vector<float>& n = normals;
	vector<int>& i = indexes;

	const float SQRT3 = sqrtf(3.f);
	// Cube

	// Vertices
	v.push_back(-0.5f); v.push_back(0.5f); v.push_back(0.f);	// 0
	v.push_back(0.5f); v.push_back(0.5f); v.push_back(0.f);		// 1
	v.push_back(0.5f); v.push_back(-0.5f); v.push_back(0.f);	// 2
	v.push_back(-0.5f); v.push_back(-0.5f); v.push_back(0.f);	// 3
	v.push_back(-0.5f); v.push_back(0.5f); v.push_back(1.f);	// 4
	v.push_back(0.5f); v.push_back(0.5f); v.push_back(1.f);		// 5
	v.push_back(0.5f); v.push_back(-0.5f); v.push_back(1.f);	// 6
	v.push_back(-0.5f); v.push_back(-0.5f); v.push_back(1.f);	// 7

	// Indexes
	// bottom
	i.push_back(1); i.push_back(0); i.push_back(2);
	i.push_back(0); i.push_back(3); i.push_back(2);

	// left
	i.push_back(4); i.push_back(7); i.push_back(0);
	i.push_back(7); i.push_back(1); i.push_back(0);

	// up
	i.push_back(4); i.push_back(5); i.push_back(6);
	i.push_back(5); i.push_back(7); i.push_back(6);

	// right
	i.push_back(6); i.push_back(5); i.push_back(2);
	i.push_back(5); i.push_back(1); i.push_back(2);

	// fw
	i.push_back(5); i.push_back(4); i.push_back(1);
	i.push_back(4); i.push_back(0); i.push_back(1);

	// bw
	i.push_back(7); i.push_back(6); i.push_back(3);
	i.push_back(6); i.push_back(2); i.push_back(3);

	// color
	c.push_back(1.0f); c.push_back(0.0f); c.push_back(0.0f); // 0
	c.push_back(1.0f); c.push_back(0.0f); c.push_back(0.0f); // 1
	c.push_back(1.0f); c.push_back(0.0f); c.push_back(0.0f); // 2
	c.push_back(1.0f); c.push_back(0.0f); c.push_back(0.0f); // 3
	c.push_back(1.0f); c.push_back(0.0f); c.push_back(0.0f); // 4
	c.push_back(1.0f); c.push_back(0.0f); c.push_back(0.0f); // 5
	c.push_back(1.0f); c.push_back(0.0f); c.push_back(0.0f); // 6
	c.push_back(1.0f); c.push_back(0.0f); c.push_back(0.0f); // 7

	// normals
	n.push_back(-1.0f / SQRT3); n.push_back(1.0f / SQRT3); n.push_back(-1.0f / SQRT3);	// 0
	n.push_back(1.0f / SQRT3); n.push_back(1.0f / SQRT3); n.push_back(-1.0f / SQRT3);	// 1
	n.push_back(1.0f / SQRT3); n.push_back(-1.0f / SQRT3); n.push_back(-1.0f / SQRT3);	// 2
	n.push_back(-1.0f / SQRT3); n.push_back(-1.0f / SQRT3); n.push_back(-1.0f / SQRT3);	// 3
	n.push_back(-1.0f / SQRT3); n.push_back(1.0f / SQRT3); n.push_back(1.0f / SQRT3);	// 4
	n.push_back(1.0f / SQRT3); n.push_back(1.0f / SQRT3); n.push_back(1.0f / SQRT3);	// 5
	n.push_back(1.0f / SQRT3); n.push_back(-1.0f / SQRT3); n.push_back(1.0f / SQRT3);	// 6
	n.push_back(-1.0f / SQRT3); n.push_back(-1.0f / SQRT3); n.push_back(1.0f / SQRT3);	// 7
}

void ZergActor::multiply()
{
	ActorsRepository::get()->createParasite(*this);
}

void ZergActor::update()
{

}

void ZergActor::render()
{
	glPushMatrix();

	if (_vbo != 0)
		glDeleteBuffers(1, &_vbo);

	glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(float) +
		colors.size() * sizeof(float) +
		normals.size() * sizeof(float),
		NULL,
		GL_STREAM_DRAW);

	GLenum error = glGetError();

	glBufferSubData(GL_ARRAY_BUFFER,
		0,
		vertices.size() * sizeof(float),
		&vertices[0]);

	error = glGetError();

	glBufferSubData(GL_ARRAY_BUFFER,
		0,
		colors.size() * sizeof(float),
		&colors[0]);

	error = glGetError();

	glBufferSubData(GL_ARRAY_BUFFER,
		0,
		normals.size() * sizeof(float),
		&normals[0]);

	error = glGetError();

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glPopMatrix();

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	//On place les pointeurs sur les datas, aux bons offsets
	glVertexPointer(3, GL_FLOAT, 0, (void*)(0));
	glColorPointer(3, GL_FLOAT, 0, (void*)(0));
	glNormalPointer(GL_FLOAT, 0, (void*)(0));

	//On demande le dessin
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
}

void ZergActor::reset()
{

}
