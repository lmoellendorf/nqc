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

/*
 * CaseStmts are used to bind a case label to another statement.  The
 * CaseStmt isn't really a statement itself - just a wrapper for
 * a single child statement.
 *
 * Upon construction CaseStmts are assigned their value and location.
 * During code generation of a switch statement, actual labels are
 * assigned to the CaseStmts within the switch.  Code generation for
 * CaseStmt itself only consists of setting the designated label to the
 * current bytecode locaiton.
 *
 */

#ifndef __CaseStmt_h
#define __CaseStmt_h

#ifndef __Stmt_h
#include "Stmt.h"
#endif

#ifndef __parser_h
#include "parser.h"
#endif

class SwitchState;

class CaseStmt : public ChainStmt
{
public:
	enum
	{
		kDefaultValue = 0x10000	// value for 'default:'
	};

			CaseStmt(int v, const LexLocation &loc, Stmt *s = 0);
			~CaseStmt();

	void	SetStmt(Stmt *s)	{ SetBody(s); }

	virtual void	EmitActual(Bytecode &b);
	virtual Stmt*	CloneActual(Mapping *b) const;

	void			EmitSwitchCases(Bytecode &b, SwitchState &s);

private:
	int		fValue;
	LexLocation fLocation;
	int		fLabel;
};


#endif
