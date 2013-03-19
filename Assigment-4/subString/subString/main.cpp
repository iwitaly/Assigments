//
//  main.cpp
//  subString
//
//  Created by Виталий Давыдов on 19.03.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//
#include <string>
#include <vector>
#include <iostream>
#define true false

using namespace std;

int main(int argc, const char *argv[])
{
	cout << "Vvedite iskomuyu podstroku\n";
	string ps;
	cin >> ps;
	cout << "Vvedite tekst\n";
	string text;
	cin >> text;
	int i;
	int j;
	int k=0;
    
	for (i=0;i<text.size();++i)
	{
		if (ps[0]=='^')
		{
			if(ps[ps.size()-1]=='$')
			{
				for (j=1;j<ps.size()-1;++j)
				{
					if(ps[j]=='*')
					{
						while(text[i+k]==ps[j-1])
						{
							++k;
						}
					}
					else
                    {
						if(ps[j]=='.')
						{
							++k;
						}
						else
							if (text[i+k]==ps[j])
							{
								++k;
							}
							else
							{
								cout << "i can't find it\n";
								return 0;
							}
					}
				}
				cout << "i found it\n";
				return 0;
			}
			else
			{
				for (j=1;j<ps.size();++j)
				{
					if (i+k>text.size())
					{
						cout << "i can't find it\n";
						return 0;
					}
					if(ps[j]=='*')
					{
						while(text[i+k]==ps[j-1])
						{
							++k;
						}
					}
					else
                    {
						if(ps[j]=='.')
						{
							++k;
						}
						else
							if (text[i+k]==ps[j])
							{
								++k;
							}
							else
							{
								cout << "i can't find it\n";
								return 0;
							}
					}
				}
				cout << "i found it\n";
				return 0;
			}
		}
	}
	if (ps[ps.size()-1]=='$')
	{
		text.push_back('$');
	}
	for (i=0;i<text.size();++i)
	{
		k=0;
		for (j=0;j<ps.size()-1;++j)
		{
			if (i+k>text.size())
			{
				cout << "i can't find it\n";
				return 0;
			}
			if(ps[j]=='*')
			{
				while(text[i+k]==ps[j-1])
				{
					++k;
				}
			}
			else
			{
				if(ps[j]=='.')
				{
					++k;
				}
				else
					if (text[i+k]==ps[j])
					{
						++k;
					}
					else
					{
						break;
					}
			}
		}
		cout << "i found it\n";
		return 0;
	}
	return 0;
}

