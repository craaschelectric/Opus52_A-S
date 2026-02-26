// ExpressionHandler.h
// Expression pedal handler - supports two types:
//
// EXPR_ANALOG:   Reads an analog pin, sends CC value = raw >> 3 (0-127)
// EXPR_DISCRETE: Counts HIGH inputs in a CWB range, CC value = count of HIGHs
//                When value changes, sends all intermediate CC values in one burst.

#ifndef EXPRESSION_HANDLER_H
#define EXPRESSION_HANDLER_H

#include "Config.h"
#include "ConfigData.h"
#include "ScanChain.h"

void expressionInit();
void processExpressions();

#endif // EXPRESSION_HANDLER_H
