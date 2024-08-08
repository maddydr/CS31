//
//  main.cpp
//  project3
//
//  Created by Maddy Delos Reyes on 10/20/22.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

bool isValidPollString(string pollData);
bool isValidUppercaseStateCode(string stateCode);
bool dataChunk(string tmpstate);
int countSeats(string pollData, char party, int& seatCount);


int main()
{
    string pollData;
        cout << "Enter poll data: ";
        getline(cin, pollData);
        
        if(!isValidPollString(pollData)) // if data is not valid (false) exit end return 1
        {
            return 1;
        }
        
        char party = 'd';
        int seatcount = 0;
        int votes = countSeats(pollData, party, seatcount);

}


bool isValidPollString(string pollData)
{
    string tmpstate;
    if (pollData == "") // valid input if input nothing
        return true;
    pollData += ','; // adds comma to end of string so it correctly chunks state poll data
    for (int i = 0; i < pollData.size(); i++) // chunk poll data by commas
    {
        if (pollData.at(i) == ' ') // if space, not valid
            return false;
        if (pollData.at(i) == ',') // if there is a comma, signifies end of states' poll data
        {
            // call new function to loop through tmpstate chunk and make sure follow poll rules
            if (!dataChunk(tmpstate))
            {
                return false;
            }
            tmpstate = ""; // sets tmpstate to empty to read in next state poll data
        }
        else // adds all chunks to temporary variable
        {
            tmpstate += pollData.at(i);
        }
        
    }
    return true;
}
  

// checking one state's poll results
bool dataChunk(string tmpstate)
{
    string statecode;
    for (int k = 0; k < 2; k++) // assigns variable statecode to just the 1st two letters to check for valid state
    {
        statecode += toupper(tmpstate.at(k));
    }
    // checking valid state code
    if (!isValidUppercaseStateCode(statecode))
    {
        return false;
    }
    // must be valid state code to proceed
    // want a string that is more than just a state and another char
    if (tmpstate.size() > 3)
    {
        // digit must be right after state code
        if (!isdigit(tmpstate.at(2)))
        {
            return false;
        }
        
        // checking for strictly only digits and alphabetical letters and making sure numbers are followed by parties
        for (int m = 2; m < tmpstate.size() - 2; m++)
        {
            if (isalpha(tmpstate.at(m)))
            {
                // makes sure the party has a number before and after it
                if (!isdigit(tmpstate.at(m - 1)) || !isdigit(tmpstate.at(m + 1)))
                    return false;
            }
            else if (!isdigit(tmpstate.at(m)))
                return false;
        }
        if (!isalpha(tmpstate.at(tmpstate.size() - 1))) // last char must be a party
            return false;
    }
        
    return true;
    
}


bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}


int countSeats(string pollData, char party, int& seatCount) // count seats function to decide how many votes for a given party
{
    if (!isValidPollString(pollData))
        return 1;
    if (!isalpha(party))
        return 2;
    
    
    string stateCode = "";
    int totalSum = 0;
    char upperParty = toupper(party); // changes party to all caps so will compare the right casings
    
    for (int i = 0; i < pollData.size(); i++)
    {
        int votes = 0;
        stateCode += toupper(pollData.at(i)); // makes all data capitalized to eliminate comparing lowercase and uppercase chars
        if (pollData.at(i) == ',' || i == pollData.size() - 1) // hit a comma or last letter, must have a chunk of state poll data
        {
            if (stateCode.size() < 4)
            {
                stateCode = "";
                continue;
            }
            if (stateCode.size() > 3)
            {
                for (int k = 2; k < stateCode.size() - 1; k++) // start after the state code
                {
                    if(isdigit(stateCode.at(k))) // checking immediately for votes after state
                    {
                        if (isdigit(stateCode.at(k + 1)) && stateCode.at(k + 2) == upperParty) // checks for another digit after 1st one, or a matching party
                        {
                            votes = static_cast<int>(stateCode.at(k)) - 48; // converts ascii value of number to intergar value
                            votes = (votes * 10);
                            totalSum = totalSum + votes;
                        }
                        else if (stateCode.at(k + 1) == upperParty) // a single digit vote? converts ascii value and adds it to cumulation of votes for particular party
                        {
                            votes = static_cast<int>(stateCode.at(k)) - 48;
                            totalSum = totalSum + votes;
                            
                        }
                    }
                }
                stateCode = ""; // sets string equal to zero ready for next state poll data
                    
            }
        }
        
    }
    seatCount = totalSum;
    return 0;
    
    
}
