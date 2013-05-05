#include "main.h"

using namespace std;

int DLL_EXPORT regex_test(char * cInput, char * cMatch)
{
	// recast input char to string
	string sInput = string(cInput);

	// setup regex
	boost::regex rx(cMatch);

    // do search
	if ( regex_search(sInput, rx) )
	{
	    return 1;
	}
	else
	{
        return 0;
	}
}

const char * DLL_EXPORT regex_match(char * cInput, char * cMatch)
{
	// recast input char to string
	string sInput = string(cInput);

	// setup regex
	boost::regex rx(cMatch);
	boost::smatch mResults;

    // run search
	if (regex_search(sInput, mResults, rx))
	{
        // convert boost::sub_match to string
		string sMatch = string() + mResults[1];

		return sMatch.c_str();
	}
	else
	{
		return (char *)"";
	}
}

int DLL_EXPORT regex_match_multiple(char * cInput, char * cMatch, char * cMatches[])
{
	// recast input char to string
	string sInput = string(cInput);

	// setup regex
	boost::smatch mResults;
	boost::regex rx(cMatch);

	// run search
	if (regex_search(sInput, mResults, rx))
	{
	    // note first match in mResults is entire matched string, which we don't want
	    // so start at 1
		for (unsigned int i = 1; i < mResults.size(); ++i)
		{
            // convert boost::sub_match to string
		    string sMatch = string() + mResults[i];

		    // copy to results array as char (for mapinfo's benefit)
			strcpy( cMatches[ i - 1 ], sMatch.c_str() );
		}

        // return number of hits
        return mResults.size() - 1;
	}
	else
	{
        // no match
		return 0;
	}
}

int DLL_EXPORT regex_match_all(char * cInput, char * cMatch, char * cMatches[])
{
	// recast niput char to string
	string sInput = string(cInput);

	// setup regex
	boost::smatch mResults;
	boost::regex rx(cMatch);
    string::const_iterator begin;

    // do search
	regex_search(sInput, mResults, rx);

    // copy matches to output array
    int submatches[] = {1};
    boost::sregex_token_iterator i(sInput.begin(), sInput.end(), rx, submatches);
    boost::sregex_token_iterator j;
    unsigned count = 0;
    while(i != j)
    {
         count++;
         strcpy( cMatches[count-1], i->str().c_str() );
         i++;
    }
    // return number of matches
	return count ;
}

int DLL_EXPORT regex_replace(char * cInput, char * cMatch, char * cReplace, char * cDest)
{
    // recast input chars to string
    string sInput = string(cInput);
    string sReplace = string(cReplace);

	// setup regex
	boost::regex rx(cMatch);

	string sReplaced = boost::regex_replace(sInput, rx, sReplace);

    strcpy( cDest, sReplaced.c_str() );
    if (sReplaced != sInput) {
        return 1;
    } else {
        return 0;
    }
}
