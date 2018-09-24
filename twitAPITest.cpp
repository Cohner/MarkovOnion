#include <ctime>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "libtwitcurl/twitcurl.h"

using namespace std;

int main(int argc, char* argv[]){
    srand(unsigned(time(0)));
    
    string consumerKey = "esJ3nFhfyNAjn9M36TjEIf9ru";
    string consumerKeySecret = "E8S3tYdtsYkw7HVtwTujrjCvdn7t6urNZP22L973SwcJpVsIwZ";
    string myAuthRequestToken = "1043687886548275201-6oAIKIcTfwBRNngHQ0vStzi1JN08an";
    string myAuthAccessTokenSecret = "V1mhfB0Z2aiiSJ9Fz17E2jcHbShcyq3Zw26bQ7SD7eKoa";
    
    string botAuthKey = "1043687886548275201-6oAIKIcTfwBRNngHQ0vStzi1JN08an";
    string botAuthKeySecret = "V1mhfB0Z2aiiSJ9Fz17E2jcHbShcyq3Zw26bQ7SD7eKoa";
    string oAuthRequestURL;
    
    
    string tempStr;
    string replyStr;
    char tempBuffer[1024];
    twitCurl twitterObj;
    
    twitterObj.setTwitterUsername("cpeg476twitbot");
    twitterObj.setTwitterPassword("Cpeg476");
    
    // Step 0
    twitterObj.getOAuth().setConsumerKey(consumerKey);
    twitterObj.getOAuth().setConsumerSecret(consumerKeySecret);
    
    // Step 1
    twitterObj.oAuthRequestToken(oAuthRequestURL);
    cout << oAuthRequestURL << endl;
    // if(twitterObj.oAuthRequestToken(myAuthRequestToken)){
    //     cout << "Request success" << endl;
    // }
    
    // Step 2
    twitterObj.oAuthHandlePIN(oAuthRequestURL);
    
    // Step 3
    twitterObj.oAuthAccessToken();
    
    // Step 4
    twitterObj.getOAuth().getOAuthTokenKey(botAuthKey);
    twitterObj.getOAuth().getOAuthTokenSecret(botAuthKeySecret);
    
    twitterObj.getOAuth().setOAuthTokenKey(botAuthKey); 
    twitterObj.getOAuth().setOAuthTokenSecret(botAuthKeySecret);
    
    tempStr = "This is a Test";
    if(twitterObj.statusUpdate(tempStr)){
        twitterObj.getLastWebResponse(replyStr);
    }else{
        twitterObj.getLastCurlError(replyStr);
        //cout << "Failed" << endl;
    }
    
    cout << replyStr << endl;
    return 0;
}