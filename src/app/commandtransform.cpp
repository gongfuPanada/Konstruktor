// Konstruktor - An interactive LDraw modeler for KDE
// Copyright (c)2006-2011 Park "segfault" J. K. <mastermind@planetmono.org>

#include <stdio.h>

#include <cmath>

#include <libldr/model.h>

#include <klocalizedstring.h>

#include "commandtransform.h"

namespace Konstruktor
{

CommandTransform::CommandTransform(bool inverse, const ldraw::matrix &matrix, const QSet<int> &selection, ldraw::model *model)
	: CommandBase(selection, model)
{
	setText(i18n("Transform"));

	inverse_ = inverse;
	matrix_ = matrix;

	for (QSet<int>::ConstIterator it = selection.constBegin(); it != selection.constEnd(); ++it) {
		if (model->elements()[*it]->get_type() == ldraw::type_ref)
			oldmatrices_[*it] = CAST_AS_CONST_REF(model->elements()[*it])->get_matrix();
	}
}

CommandTransform::CommandTransform(bool inverse, const QSet<int> &selection, ldraw::model *model)
	: CommandBase(selection, model)
{
	setText(i18n("Transform"));

	inverse_ = inverse;

	for (QSet<int>::ConstIterator it = selection.constBegin(); it != selection.constEnd(); ++it) {
		if (model->elements()[*it]->get_type() == ldraw::type_ref)
			oldmatrices_[*it] = CAST_AS_CONST_REF(model->elements()[*it])->get_matrix();
	}
}

CommandTransform::~CommandTransform()
{

}

bool CommandTransform::needUpdateDimension() const
{
	return true;
}

void CommandTransform::redo()
{
	for (QSet<int>::ConstIterator it = selection_.constBegin(); it != selection_.constEnd(); ++it) {
		if (model_->elements()[*it]->get_type() == ldraw::type_ref) {
			ldraw::element_ref *r = CAST_AS_REF(model_->elements()[*it]);
			ldraw::matrix cmat;
			if (inverse_)
				cmat = matrix_ * r->get_matrix();
			else
				cmat = r->get_matrix() * matrix_;
			
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					float e = cmat.value(i, j);
					if (std::fabs(std::fabs(e) - 1.0f) < LDR_EPSILON)
						cmat.value(i, j) = e > 0.0f ? 1.0f:-1.0f;
					else if (std::fabs(e) < LDR_EPSILON)
						cmat.value(i, j) = 0.0f;
					else if (std::fabs(std::fabs(e) - 0.707106f) < LDR_EPSILON)
						cmat.value(i, j) = e > 0.0f ? 0.707106f:-0.707106f;
					else if (std::fabs(std::fabs(e) - 0.5f) < LDR_EPSILON)
						cmat.value(i, j) = e > 0.0f ? 0.5f:-0.5f;
					else if (std::fabs(std::fabs(e) - 0.866025f) < LDR_EPSILON)
						cmat.value(i, j) = e > 0.0f ? 0.866025f:-0.866025f;
				}
			}

			r->set_matrix(cmat);
		}
	}
}

void CommandTransform::undo()
{
	for (QSet<int>::ConstIterator it = selection_.constBegin(); it != selection_.constEnd(); ++it) {
		if (model_->elements()[*it]->get_type() == ldraw::type_ref)
			CAST_AS_REF(model_->elements()[*it])->set_matrix(oldmatrices_[*it]);
	}
}

}