// Konstruktor - An interactive LDraw modeler for KDE
// Copyright (c)2006-2011 Park "segfault" J. K. <mastermind@planetmono.org>

#ifndef _COMMANDTRANSFORM_H_
#define _COMMANDTRANSFORM_H_

#include <QMap>

#include <libldr/math.h>

#include "commandbase.h"

namespace Konstruktor
{

class CommandTransform : public CommandBase
{
  public:
	CommandTransform(bool inverse, const ldraw::matrix &matrix, const QSet<int> &selection, ldraw::model *model);	
	CommandTransform(bool inverse, const QSet<int> &selection, ldraw::model *model);
	virtual ~CommandTransform();

	bool needUpdateDimension() const;
	
	void redo();
	void undo();

  protected:
	bool inverse_;
	ldraw::matrix matrix_;
	std::map<int, ldraw::matrix> oldmatrices_;
};

}

#endif