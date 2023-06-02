#include "SyntaxAnalysis.h"
#include <iostream>

SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lexicalAnalysis) : m_lexicalAnalysis(lexicalAnalysis), m_syntaxError(false)
{
	m_tokenIterator = m_lexicalAnalysis.getTokenList().begin();
}

bool SyntaxAnalysis::doSyntaxAnalysis() {
	
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
		m_currentToken.printTokenInfo();
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
		throw std::runtime_error("End of input file reached!");
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
		printSyntaxError(m_currentToken);
	}

}

void SyntaxAnalysis::s()
{
	if (m_syntaxError == true)
	{
		return;
	}

	if (m_currentToken.getType() == T_MEM)
	{
		eat(T_MEM);

		if (m_currentToken.getType() == T_M_ID)
		{
			eat(T_M_ID);
			
			if (m_currentToken.getType() == T_NUM)
			{
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
		//std::cout << "Syntax OK" << std::endl;
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

	if (m_currentToken.getType() == T_ADD)
	{
		eat(T_ADD);
		if (m_currentToken.getType() == T_R_ID)
		{
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_R_ID)
						{
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
		if (m_currentToken.getType() == T_R_ID)
		{
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_NUM)
						{
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
		if (m_currentToken.getType() == T_R_ID)
		{
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_R_ID)
						{
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
		if (m_currentToken.getType() == T_R_ID)
		{
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_M_ID)
				{
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
		if (m_currentToken.getType() == T_R_ID)
		{
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_NUM)
				{
					eat(T_NUM);
					if (m_currentToken.getType() == T_L_PARENT)
					{
						eat(T_L_PARENT);
						if (m_currentToken.getType() == T_R_ID)
						{
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
		if (m_currentToken.getType() == T_R_ID)
		{
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_NUM)
				{
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
		if (m_currentToken.getType() == T_R_ID)
		{
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_NUM)
				{
					eat(T_NUM);
					if (m_currentToken.getType() == T_L_PARENT)
					{
						eat(T_L_PARENT);
						if (m_currentToken.getType() == T_R_ID)
						{
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
		if (m_currentToken.getType() == T_ID)
		{
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
		if (m_currentToken.getType() == T_R_ID)
		{
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_ID)
				{
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
	}
	// syntax analysis for newest tokens
	else if (m_currentToken.getType() == T_REM)
	{
		eat(T_REM);
		if (m_currentToken.getType() == T_R_ID)
		{
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_R_ID)
						{
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
	else if (m_currentToken.getType() == T_SEQ)
	{
		eat(T_SEQ);
		if (m_currentToken.getType() == T_R_ID)
		{
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_R_ID)
						{
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
	else if (m_currentToken.getType() == T_BEQ)
	{
		eat(T_BEQ);
		if (m_currentToken.getType() == T_R_ID)
		{
			eat(T_R_ID);
			if (m_currentToken.getType() == T_COMMA)
			{
				eat(T_COMMA);
				if (m_currentToken.getType() == T_R_ID)
				{
					eat(T_R_ID);
					if (m_currentToken.getType() == T_COMMA)
					{
						eat(T_COMMA);
						if (m_currentToken.getType() == T_ID)
						{
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
}