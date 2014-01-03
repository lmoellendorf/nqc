/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * The Initial Developer of this code is David Baum.
 * Portions created by David Baum are Copyright (C) 1999 David Baum.
 * All Rights Reserved.
 *
 * Portions created by John Hansen are Copyright (C) 2005 John Hansen.
 * All Rights Reserved.
 *
 */
#include <cstring>
#include "Expansion.h"
#include "Macro.h"
#include "parser.h"
#include "Symbol.h"

using std::memcpy;

Expansion::Expansion(Macro *def)
{
	fDef = def;
	fDef->SetMark();
	fTokens = def->GetTokens();
	fEnd = fTokens + def->GetTokenCount();
	fArgCount = def->GetArgCount();
	if (fArgCount > 0)
	{
		fArgs = new Token*[fArgCount];
		fArgLengths = new int[fArgCount];
		for(int i=0; i<fArgCount; i++)
		{
			fArgs[i] = nil;
			fArgLengths[i] = 0;
		}
	}
	else
	{
		fArgs = nil;
		fArgLengths = nil;
	}
}


Expansion::Expansion(const Expansion *e, int i)
{
	fDef = nil;
	fTokens = e->fArgs[i];
	fEnd = fTokens + e->fArgLengths[i];
	fArgCount = 0;
	fArgs = nil;
	fArgLengths = nil;
}


Expansion::~Expansion()
{
	if (fDef) fDef->ClearMark();
	if (fArgs)
	{
		for(int i=0; i<fArgCount; i++)
			delete [] fArgs[i];
		delete [] fArgs;
	}
	delete [] fArgLengths;
}


int Expansion::NextToken(TokenVal &v)
{
	int t;

	t = fTokens->fType;
	v = fTokens->fValue;

	fTokens++;
	return t;
}


void Expansion::SetArg(int i, const Token *t, int count)
{
	Token *tokens = new Token[count];
	memcpy(tokens, t, count * sizeof(Token));

	fArgs[i] = tokens;
	fArgLengths[i] = count;
}
