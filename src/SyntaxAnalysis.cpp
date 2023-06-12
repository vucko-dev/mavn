/* Autor: David Vucenovic Datum: 02.06.2023. */



#include "SyntaxAnalysis.h"


SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lexicalAnalysis, Instructions* instructions, Variables* memoryVariables, Variables* registerVariables) : m_lexicalAnalysis(lexicalAnalysis), m_instructions(instructions), m_memVars(memoryVariables), m_regVars(registerVariables),  m_syntaxError(false), m_instructionCounter(0), m_variableCounter(0)
{
	m_tokenIterator = m_lexicalAnalysis.getTokenList().begin();
}

bool SyntaxAnalysis::doSyntaxAnalysis() 
{
	
	m_currentToken = getNextToken();

	//Starting analysis with nonterminal symbol
	q();

	return !m_syntaxError;

}

void SyntaxAnalysis::printSyntaxError(Token& token)
{
	std::cout << "Syntax error! Token: " << token.getValue() << " unexpected." << std::endl;
}

void SyntaxAnalysis::eat(TokenType t)
{
	if (m_currentToken.getType() == t)
	{
		if (m_currentToken.getType() == T_END_OF_FILE)
		{
			return;
		}
		else
		{
			m_currentToken = getNextToken();
		}
	}
	else
	{
		printSyntaxError(m_currentToken);
	}
}

Token SyntaxAnalysis::getNextToken()
{
	if (m_tokenIterator == m_lexicalAnalysis.getTokenList().end())
	{		
		throw EndInputReached();
	}

	return *m_tokenIterator++;
}

void SyntaxAnalysis::q()
{
	if (m_syntaxError == true)
	{
		return;
	}

	s();

	if (m_currentToken.getType() == T_SEMI_COL)
	{
		eat(T_SEMI_COL);
		l();
	}
	else
	{
		m_syntaxError = true;
		//printSyntaxError(m_currentToken);
	}

}

void SyntaxAnalysis::s()
{
	if (m_syntaxError == true)
	{
		return;
	}

	Variable *var = NULL;
	Instruction *instruction = NULL;

	if (m_currentToken.getType() == T_MEM)
	{
		eat(T_MEM);

		if (m_currentToken.getType() == T_M_ID)
		{

			std::string variableName = m_currentToken.getValue();

			eat(T_M_ID);
			
			if (m_currentToken.getType() == T_NUM)
			{
				std::string variableValue = m_currentToken.getValue();
				var = new Variable(variableName, Variable::MEM_VAR, stoi(variableValue));
				addVariable(var);
				eat(T_NUM);
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
		else
		{
			m_syntaxError = true;
			printSyntaxError(m_currentToken);
		}

	} 
	else if (m_currentToken.getType() == T_REG)
	{
		eat(T_REG);

		if (m_currentToken.getType() == T_R_ID)
		{
			std::string variableName = m_currentToken.getValue();
			var = new Variable(variableName, Variable::REG_VAR);
			//var->setAssignment(getNewReg()); When Livnees come
			var->isVariableCorrect();
			addVariable(var);
			eat(T_R_ID);
		}
		else
		{
			m_syntaxError = true;
			printSyntaxError(m_currentToken);
		}
	}
	else if (m_currentToken.getType() == T_FUNC)
	{
		eat(T_FUNC);
		if (m_currentToken.getType() == T_ID)
		{
			instruction = new Instruction(I_NO_TYPE, m_instructionCounter++);

			Label* label = new Label(m_currentToken.getValue(), Label::FUNCTION_ID);
			addLabel(label);
			instruction->addLabel(label);
			m_instructions->push_back(instruction);
			eat(T_ID);
		}
		else
		{
			m_syntaxError = true;
			printSyntaxError(m_currentToken);
		}
	}
	else if (m_currentToken.getType() == T_ID)
	{
		instruction = new Instruction(I_NO_TYPE, m_instructionCounter++);
		Label *label = new Label(m_currentToken.getValue(), Label::ID);
		addLabel(label);
		instruction->addLabel(label);
		m_instructions->push_back(instruction);
		eat(T_ID);
		if (m_currentToken.getType() == T_COL)
		{
			eat(T_COL);
			e();
		}
		else
		{
			m_syntaxError = true;
			printSyntaxError(m_currentToken);
		}
	}
	else
	{
		e();
	}
}

void SyntaxAnalysis::l()
{
	if (m_syntaxError == true)
	{
		return;
	}

	if (m_currentToken.getType() == T_END_OF_FILE)
	{
		eat(T_END_OF_FILE);
	}
	else
	{
		q();
	}
}

void SyntaxAnalysis::e()
{
	if (m_syntaxError == true)
	{
		return;
	}

	Instruction* instruction = NULL;
	Variables srcVariables;
	Variables destVariables;

	if (m_currentToken.getType() == T_ADD)
	{
		eat(T_ADD);
		instruction = new Instruction(I_ADD, m_instructionCounter++);
		if (m_currentToken.getType() == T_R_ID)
		{
			destVariables.push_back(getVariable(m_currentToken.getValue()));
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{

				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					srcVariables.push_back(getVariable(m_currentToken.getValue()));
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_R_ID)
						{
							srcVariables.push_back(getVariable(m_currentToken.getValue()));
							eat(T_R_ID);
						}
						else
						{
							m_syntaxError = true;
							printSyntaxError(m_currentToken);
						}
					}
					else
					{
						m_syntaxError = true;
						printSyntaxError(m_currentToken);
					}
				}
				else
				{
					m_syntaxError = true;
					printSyntaxError(m_currentToken);
				}
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
	}
	else if (m_currentToken.getType() == T_ADDI)
	{
		eat(T_ADDI);
		instruction = new Instruction(I_ADDI, m_instructionCounter++);
		if (m_currentToken.getType() == T_R_ID)
		{
			destVariables.push_back(getVariable(m_currentToken.getValue()));
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					srcVariables.push_back(getVariable(m_currentToken.getValue()));
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_NUM)
						{
							Variable *variable = new Variable();
							variable->setValue(stoi(m_currentToken.getValue()));
							srcVariables.push_back(variable);
							eat(T_NUM);
						}
						else
						{
							m_syntaxError = true;
							printSyntaxError(m_currentToken);
						}
					}
					else
					{
						m_syntaxError = true;
						printSyntaxError(m_currentToken);
					}
				}
				else
				{
					m_syntaxError = true;
					printSyntaxError(m_currentToken);
				}
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
	}
	else if (m_currentToken.getType() == T_SUB)
	{
		eat(T_SUB);
		instruction = new Instruction(I_SUB,m_instructionCounter++);
		if (m_currentToken.getType() == T_R_ID)
		{
			destVariables.push_back(getVariable(m_currentToken.getValue()));
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					srcVariables.push_back(getVariable(m_currentToken.getValue()));
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_R_ID)
						{
							srcVariables.push_back(getVariable(m_currentToken.getValue()));
							eat(T_R_ID);
						}
						else
						{
							m_syntaxError = true;
							printSyntaxError(m_currentToken);
						}
					}
					else
					{
						m_syntaxError = true;
						printSyntaxError(m_currentToken);
					}
				}
				else
				{
					m_syntaxError = true;
					printSyntaxError(m_currentToken);
				}
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
	}
	else if (m_currentToken.getType() == T_LA)
	{
		eat(T_LA);
		instruction = new Instruction(I_LA, m_instructionCounter++);
		if (m_currentToken.getType() == T_R_ID)
		{
			destVariables.push_back(getVariable(m_currentToken.getValue()));
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_M_ID)
				{
					srcVariables.push_back(getVariable(m_currentToken.getValue()));
					eat(T_M_ID);
				}
				else
				{
					m_syntaxError = true;
					printSyntaxError(m_currentToken);
				}
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
		else
		{
			m_syntaxError = true;
			printSyntaxError(m_currentToken);
		}
	}
	else if (m_currentToken.getType() == T_LW)
	{
		eat(T_LW);
		instruction = new Instruction(I_LW, m_instructionCounter++);
		if (m_currentToken.getType() == T_R_ID)
		{
			destVariables.push_back(getVariable(m_currentToken.getValue()));
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_NUM)
				{
					Variable* variable = new Variable();
					variable->setValue(stoi(m_currentToken.getValue()));
					srcVariables.push_back(variable);
					eat(T_NUM);
					if (m_currentToken.getType() == T_L_PARENT)
					{
						eat(T_L_PARENT);
						if (m_currentToken.getType() == T_R_ID)
						{
							srcVariables.push_back(getVariable(m_currentToken.getValue()));
							eat(T_R_ID);
							if (m_currentToken.getType() == T_R_PARENT)
							{
								eat(T_R_PARENT);
							}
							else
							{
								m_syntaxError = true;
								printSyntaxError(m_currentToken);
							}
						}
						else
						{
							m_syntaxError = true;
							printSyntaxError(m_currentToken);
						}
					}
					else
					{
						m_syntaxError = true;
						printSyntaxError(m_currentToken);
					}
				}
				else
				{
					m_syntaxError = true;
					printSyntaxError(m_currentToken);
				}
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
		else
		{
			m_syntaxError = true;
			printSyntaxError(m_currentToken);
		}
	}
	else if (m_currentToken.getType() == T_LI)
	{
		eat(T_LI);
		instruction = new Instruction(I_LI, m_instructionCounter++);

		if (m_currentToken.getType() == T_R_ID)
		{
			destVariables.push_back(getVariable(m_currentToken.getValue()));
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_NUM)
				{
					Variable* variable = new Variable();
					variable->setValue(stoi(m_currentToken.getValue()));
					srcVariables.push_back(variable);
					eat(T_NUM);
				}
				else
				{
					m_syntaxError = true;
					printSyntaxError(m_currentToken);
				}
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
		else
		{
			m_syntaxError = true;
			printSyntaxError(m_currentToken);
		}
	}
	else if (m_currentToken.getType() == T_SW)
	{
		eat(T_SW);
		instruction = new Instruction(I_SW, m_instructionCounter++);
		if (m_currentToken.getType() == T_R_ID)
		{
			destVariables.push_back(getVariable(m_currentToken.getValue()));
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_NUM)
				{
					Variable* variable = new Variable();
					variable->setValue(stoi(m_currentToken.getValue()));
					srcVariables.push_back(variable);
					eat(T_NUM);
					if (m_currentToken.getType() == T_L_PARENT)
					{
						eat(T_L_PARENT);
						if (m_currentToken.getType() == T_R_ID)
						{
							srcVariables.push_back(getVariable(m_currentToken.getValue()));
							eat(T_R_ID);
							if (m_currentToken.getType() == T_R_PARENT)
							{
								eat(T_R_PARENT);
							}
							else
							{
								m_syntaxError = true;
								printSyntaxError(m_currentToken);
							}
						}
						else
						{
							m_syntaxError = true;
							printSyntaxError(m_currentToken);
						}
					}
					else
					{
						m_syntaxError = true;
						printSyntaxError(m_currentToken);
					}
				}
				else
				{
					m_syntaxError = true;
					printSyntaxError(m_currentToken);
				}
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
		else
		{
			m_syntaxError = true;
			printSyntaxError(m_currentToken);
		}
	}
	else if (m_currentToken.getType() == T_B)
	{
		eat(T_B);
		instruction = new Instruction(I_B, m_instructionCounter++);
		if (m_currentToken.getType() == T_ID)
		{
			instruction->addLabel(getLabel(m_currentToken.getValue()));
			eat(T_ID);
		}
		else
		{
			m_syntaxError = true;
			printSyntaxError(m_currentToken);
		}
	}
	else if (m_currentToken.getType() == T_BLTZ)
	{
		eat(T_BLTZ);
		instruction = new Instruction(I_BLTZ, m_instructionCounter++);
		if (m_currentToken.getType() == T_R_ID)
		{
			srcVariables.push_back(getVariable(m_currentToken.getValue()));
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_ID)
				{
					instruction->addLabel(getLabel(m_currentToken.getValue()));
					eat(T_ID);
				}
				else
				{
					m_syntaxError = true;
					printSyntaxError(m_currentToken);
				}
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
		else
		{
			m_syntaxError = true;
			printSyntaxError(m_currentToken);
		}
	}
	else if (m_currentToken.getType() == T_NOP)
	{
		eat(T_NOP);
		instruction = new Instruction(I_NOP, m_instructionCounter++);
	}
	// syntax analysis for newest tokens
	else if (m_currentToken.getType() == T_OR)
	{
		eat(T_OR);
		instruction = new Instruction(I_OR, m_instructionCounter++);
		if (m_currentToken.getType() == T_R_ID)
		{
			destVariables.push_back(getVariable(m_currentToken.getValue()));
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					srcVariables.push_back(getVariable(m_currentToken.getValue()));
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_R_ID)
						{
							srcVariables.push_back(getVariable(m_currentToken.getValue()));
							eat(T_R_ID);
						}
						else
						{
							m_syntaxError = true;
							printSyntaxError(m_currentToken);
						}
					}
					else
					{
						m_syntaxError = true;
						printSyntaxError(m_currentToken);
					}
				}
				else
				{
					m_syntaxError = true;
					printSyntaxError(m_currentToken);
				}
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
	}
	else if (m_currentToken.getType() == T_SGE)
	{
		eat(T_SGE);
		instruction = new Instruction(I_SGE, m_instructionCounter++);
		if (m_currentToken.getType() == T_R_ID)
		{
			destVariables.push_back(getVariable(m_currentToken.getValue()));
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					srcVariables.push_back(getVariable(m_currentToken.getValue()));
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_R_ID)
						{
							srcVariables.push_back(getVariable(m_currentToken.getValue()));

							eat(T_R_ID);
						}
						else
						{
							m_syntaxError = true;
							printSyntaxError(m_currentToken);
						}
					}
					else
					{
						m_syntaxError = true;
						printSyntaxError(m_currentToken);
					}
				}
				else
				{
					m_syntaxError = true;
					printSyntaxError(m_currentToken);
				}
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
	}
	else if (m_currentToken.getType() == T_BNE)
	{
		eat(T_BNE);
		instruction = new Instruction(I_BNE, m_instructionCounter++);
		if (m_currentToken.getType() == T_R_ID)
		{
			destVariables.push_back(getVariable(m_currentToken.getValue()));
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					destVariables.push_back(getVariable(m_currentToken.getValue()));
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_ID)
						{
							instruction->addLabel(getLabel(m_currentToken.getValue()));
							eat(T_ID);
						}
						else
						{
							m_syntaxError = true;
							printSyntaxError(m_currentToken);
						}
					}
					else
					{
						m_syntaxError = true;
						printSyntaxError(m_currentToken);
					}
				}
				else
				{
					m_syntaxError = true;
					printSyntaxError(m_currentToken);
				}
			}
			else
			{
				m_syntaxError = true;
				printSyntaxError(m_currentToken);
			}
		}
	}
	else
	{
		m_syntaxError = true;
		printSyntaxError(m_currentToken);
	}

	if (instruction != NULL)
	{
		if (srcVariables.empty() == false)
		{
			instruction->addSrc(srcVariables);
		}
		if (destVariables.empty() == false)
		{
			instruction->addDest(destVariables);
		}

		m_instructions->push_back(instruction);
		return;
	}
}

bool SyntaxAnalysis::variableExists(Variable* var) 
{
	if (find(m_memVars->begin(), m_memVars->end(), var) == m_memVars->end() && find(m_regVars->begin(), m_regVars->end(), var) == m_regVars->end())
	{
		return false;
	}
	throw VariableExistsError(var->getName());
	return true;
}

void SyntaxAnalysis::addVariable(Variable* var) 
{
	if (variableExists(var) == true) 
	{
		return;
	}
	else
	{
		if (var->getType() == Variable::MEM_VAR)
		{
			m_memVars->push_back(var);
		}
		else if (var->getType() == Variable::REG_VAR)
		{
			var->setPosition(m_variableCounter++);
			m_regVars->push_back(var);
		}
	}
}

bool SyntaxAnalysis::labelExists(Label* label)
{
	if (find(m_labels.begin(), m_labels.end(), label) == m_labels.end())
	{
		return false;
	}
	throw LabelExistsError(label->getName());
	return true;
}

void SyntaxAnalysis::addLabel(Label* label)
{
	if (labelExists(label) == true)
	{
		return;
	}
	else
	{
		m_labels.push_back(label);
	}
}

Variable* SyntaxAnalysis::getVariable(std::string name)
{
	for (Variable* variable : *m_regVars)
	{
		if (variable->getName() == name)
		{
			return variable;
		}
	}

	for (Variable* variable : *m_memVars)
	{
		if (variable->getName() == name)
		{
			return variable;
		}
	}

	throw VariableNotDefinedError(name);
}

Label* SyntaxAnalysis::getLabel(std::string name)
{
	for (Label* label : m_labels)
	{
		if (label->getName() == name)
		{
			return label;
		}
	}
	throw LabelNotDefinedError(name);

	return NULL;
}