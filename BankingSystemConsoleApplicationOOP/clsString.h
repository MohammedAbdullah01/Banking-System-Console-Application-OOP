#pragma once
#include <iostream>
#include <vector>

using namespace std;

class clsString
{
private:
	string _Value;

public:
	clsString()
	{
		_Value = "";
	}

	clsString(string value)
	{
		_Value = value;
	}

	string getValue()
	{
		return _Value;
	}

	void setValue(string value)
	{
		_Value = value;
	}

	__declspec(property(get = getValue, put = setValue)) string value;


	static string UppercaseFirstLetterOfEachWord(string str)
	{
		bool flag = true;

		for (short i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ' && flag)
			{
				str[i] = toupper(str[i]);
				flag = false;
			}
			else if (str[i] == ' ')
			{
				flag = true;
			}
		}
		return str;
	}

	void UppercaseFirstLetterOfEachWord()
	{
		_Value = UppercaseFirstLetterOfEachWord(_Value);
	}

	static string LowercaseFirstLetterOfEachWord(string str)
	{
		bool flag = true;

		for (short i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ' && flag)
			{
				str[i] = tolower(str[i]);
				flag = false;
			}
			else if (str[i] == ' ')
			{
				flag = true;
			}
		}
		return str;
	}

	void LowercaseFirstLetterOfEachWord()
	{
		_Value = LowercaseFirstLetterOfEachWord(_Value);
	}

	static string UpperAllLetters(string str)
	{
		for (short i = 0; i < str.length(); i++)
		{
			str[i] = toupper(str[i]);
		}
		return str;
	}

	void UpperAllLetters()
	{
		_Value = UpperAllLetters(_Value);
	}

	static string LowerAllLetters(string str)
	{
		for (short i = 0; i < str.length(); i++)
		{
			str[i] = tolower(str[i]);
		}
		return str;
	}

	void LowerAllLetters()
	{
		_Value = LowerAllLetters(_Value);
	}

	static char InvertLetterCase(char character)
	{
		return (isupper(character)) ? tolower(character) : toupper(character);
	}

	static string InvertAllStringLettersCase(string str)
	{
		for (short i = 0; i < str.length(); i++)
		{
			str[i] = InvertLetterCase(str[i]);
		}
		return str;
	}

	void InvertAllStringLettersCase()
	{
		_Value = InvertAllStringLettersCase(_Value);
	}

	enum enWhatToCount
	{
		CapitalLetters = 1, SmallLetters = 2 , All = 3
	};

	static short CountLetters(string str, enWhatToCount whatToCount = enWhatToCount::SmallLetters)
	{
		short counter = 0;
		for (short i = 0; i < str.length(); i++)
		{
			if (whatToCount == enWhatToCount::CapitalLetters && isupper(str[i]))
				counter++;

			if (whatToCount == enWhatToCount::SmallLetters && islower(str[i]))
				counter++;
		}
		return counter;
	}
	
	static short CountSmallLettersInString(string str)
	{
		short counter = 0;
		for (short i = 0; i < str.length(); i++)
		{
			if (islower(str[i]))
			{
				counter++;
			}
		}
		return counter;
	}

	short CountSmallLettersInString()
	{
		return CountSmallLettersInString(_Value);
	}

	static short CountCapitalLettersInString(string str)
	{
		short counter = 0;
		for (short i = 0; i < str.length(); i++)
		{
			if (isupper(str[i]))
			{
				counter++;
			}
		}
		return counter;
	}

	short CountCapitalLettersInString()
	{
		return CountCapitalLettersInString(_Value);
	}

	static short HowManyRecurringcharacters(string str, char findLetter, bool matchCase = true)
	{
		short counter = 0;
		for (short i = 0; i < str.length(); i++)
		{
			if (matchCase)
			{
				if (str[i] == findLetter)
					counter++;
			}
			else
			{
				if (toupper(findLetter) == str[i] || tolower(findLetter) == str[i])
					counter++;
			}
		}
		return counter;
	}

	short HowManyRecurringcharacters(char findLetter, bool matchCase = true) 
	{
		return HowManyRecurringcharacters(_Value , findLetter , matchCase);
	}

	enum enVowels { a = 97, e = 101, i = 105, o = 111, u = 117 };

	static bool IsVowel(char letter)
	{
		letter = tolower(letter);
		return (letter == (char) (enVowels::a) ||
			letter == static_cast<char>(enVowels::e) ||
			letter == static_cast<char>(enVowels::i) ||
			letter == static_cast<char>(enVowels::o) ||
			letter == static_cast<char>(enVowels::u));
	}

	static short CountVowels(string str)
	{
		short counter = 0;
		for (char& letter : str)
		{
			if (IsVowel(letter))
			{
				counter++;
			}
		}
		return counter;
	}

	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static short CountEachWordInString(string str, string delimter)
	{
		size_t position = 0;
		short counter = 0;
		string word;

		while ((position = str.find(delimter)) != string::npos)
		{
			word = str.substr(0, position);

			if (!word.empty())
			{
				counter++;
			}
			str.erase(0, position + delimter.length());
		}

		if (!str.empty())
		{
			counter++;
		}

		return counter;
	}

	short CountEachWordInString(string delimter)
	{
		return CountEachWordInString(_Value, delimter);
	}

	static vector<string> SplitEachWordInVector(string str, string delimter)
	{
		size_t position = 0;
		string word;
		vector<string> vWords;

		while ((position = str.find(delimter)) != string::npos)
		{
			word = str.substr(0, position);

			if (!word.empty())
			{
				vWords.push_back(word);
			}

			str.erase(0, position + delimter.length());
		}

		if (!str.empty())
		{
			vWords.push_back(str);
		}
		return vWords;
	}

	vector<string> SplitEachWordInVector(string delimter)
	{
		return SplitEachWordInVector(_Value, delimter);
	}

	static string TrimRightString(string str)
	{
		for (size_t i = str.length() - 1; i > 0; i--)
		{
			if (str[i] != ' ')
			{
				return str.substr(0, i + 1);
			}
		}
		return str;
	}

	void TrimRightString()
	{
		_Value = TrimRightString(_Value);
	}

	static string TrimLeftString(string str)
	{
		for (size_t i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ')
			{
				return str.substr(i, str.length() - 1);
			}
		}
		return "";
	}

	void TrimLeftString()
	{
		_Value = TrimLeftString(_Value);
	}

	static string TrimString(string str)
	{
		return TrimRightString(TrimLeftString(str));
	}

	void TrimString()
	{
		_Value = TrimString(_Value);
	}

	static string JoinString(vector<string> vWord, string delimter)
	{
		string str = "";
		for (short i = 0; i < vWord.size(); i++)
		{
			str += vWord[i];
			str += (i != vWord.size() - 1) ? delimter : "";
		}
		return str;
	}

	static string JoinString(string arr[], short arrLength, string delimter)
	{
		string str = "";
		for (short i = 0; i < arrLength; i++)
		{
			str += arr[i];
			str += (i != arrLength - 1) ? delimter : "";
		}
		return str;
	}

	static string ReverseWords(string str)
	{
		vector <string> vWords = SplitEachWordInVector(str, " ");
		string result = "";
		vector <string>::iterator iter = vWords.end();
		while (iter != vWords.begin())
		{
			--iter;
			result += *iter;

			if (iter != vWords.begin())
				result += " ";
		}
		return result;
	}

	void ReverseWords()
	{
		_Value = ReverseWords(_Value);
	}

	static string ReplaceString(string str, string stringToReplace, string replaseTo, bool matchCase = true)
	{
		vector <string> vWords = SplitEachWordInVector(str, " ");

		for (string& word : vWords)
		{
			if (matchCase)
			{
				if (stringToReplace == word)
				{
					word = replaseTo;
				}
			}
			else {
				if (LowerAllLetters(stringToReplace) == LowerAllLetters(word))
				{
					word = replaseTo;
				}
			}
		}
		return JoinString(vWords, " ");
	}

	string ReplaceString(string stringToReplace, string replaseTo, bool matchCase = true)
	{
		return ReplaceString(_Value, stringToReplace , replaseTo, matchCase);
	}

	static bool IsPunctuation(char Punc)
	{
		switch (Punc)
		{
		case '?':return true;
		case '}':return true;
		case '{':return true;
		case ',':return true;
		case '.':return true;
		case '-':return true;
		case '_':return true;
		case ']':return true;
		case '[':return true;
		case '(':return true;
		case ')':return true;
		case '!':return true;
		case ';':return true;
		case ':':return true;
		case '`':return true;
		}
		return false;
	}

	static string RemovePunctuationFromString(string str)
	{
		string result = "";
		for (short i = 0; i < str.length(); i++)
		{
			if (!IsPunctuation(str[i]))
			{
				result += str[i];
			}
		}
		return result;
	}

	void RemovePunctuationFromString()
	{
		_Value = RemovePunctuationFromString(_Value);
	}

	static string replaceWordInString(string str, string toReplace, string replacement)
	{
		if (toReplace.empty())
		{
			return str;
		}

		size_t i = 0;
		string result = "";
		while (i < str.length())
		{
			if (str.substr(i, toReplace.length()) == toReplace)
			{
				result += replacement;
				i += toReplace.length();
			}
			else
			{
				result += str[i];
				i++;
			}
		}
		return result;
	}

	void replaceWordInString(string toReplace, string replacement)
	{
		_Value =  replaceWordInString(_Value , toReplace , replacement);
	}

};

