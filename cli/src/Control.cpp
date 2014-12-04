////////////////////////////////////////////////////////////
// Control functions for taking data parsed by "options" 
// and calling other functions, 
// then writing status updates to output file.


Control::Control( Options optionsContainer) {}  // Constructor

~Control::Control()               // Destructor
{
}

//bool Control::run(void){}
//String Control::getStatus(){
  addMsg(fileVec, "Status=",opt.getCurrentStatus();
  Control::writeVec(fileVec, tmpFile);
}
void Control::newSession(Options opt){
  addMsg(fileVec, "SessionID=", opt.getSessionID() );
  addMsg(fileVec, "Action=", opt.getAction() );
  Control::writeVec(fileVec, tmpFile);
}
//void Control::openSession(){}
//void Control::refreshSession(){}
//void Control::closeSession(){}
//void Control::encryptFiles(){}
//void Control::decryptFiles(){}


////////////////////////////////////////////////////////////
// Function to write vector of strings to file.
// In main have data to be sent to GUI appended to a vector<string>
// Once all functions have added their status/messages
// Call this function to write them to the output file.

int Control::writeVec(std::vector<std::string> &lines, std::string targetFile)
{
    std::ofstream outfile;
    int i=0;
	
	struct stat buf;                                          // If there is already a file of this name, delete it.
    if( stat( targetFile.c_str(), &buf ) != -1) remove( targetFile.c_str() );
	
    outfile.open(targetFile.c_str(),std::ios::app);         // Open the file and write contents of vector to it.
	if(!outfile) return 1;	
    for (i=0; i < lines.size(); i++ ) outfile << lines[i] << std::endl;
	lines.clear();                                            // Clear the vector.
    outfile.close();
	return 0;
}//end funct write.






////////////////////////////////////////////////////////////
// Function to build string from pair of strings and append
// that string into vector<string>
// example call coudl be addMsg("^!error ", errorMessage[i] );
// or addMsg("^!error ", "No session ID given!" );

int Control::addMsg(std::vector<std::string> &vec, std::string arg1, std::string arg2 )
{
  if(vec == NULL) return 1;
  arg1.append(arg2);
  vec.push_back(arg1);
  return 0;
}// end add string function.

////////////////////////////////////////////////////////////
// Function to build string from a string and an int and append
// that string into vector<string>

int Control::addMsg(std::vector<std::string> &vec, std::string arg1, int arg2 )
{
  if(vec == NULL) return 1;
  char tmp[16]={'\0'};
  sprintf(tmp,"%i",arg2);
  arg1.append(tmp);
  vec.push_back(arg1);
  return 0;
}// end add string function.


/*
// Notes on this stuff from meeting..
Data Flags used in output file:
  ^!error
  ^!fatal
        File Contents:
          --start_session (decimal)
          --refresh_session (1/0)
          --encrypt -running status 
                        (everyline)
                          # overall(files done), # total, current(path, blocks done, blocks total), overall(blocks done, blocks total)
          --decrypt -running status 
                        (everyline)
                          # overall(files done), # total, current(path, blocks done, blocks total), overall(blocks done, blocks total)
          --discovery (1/0)
          --Close_session (done)
EX file-encrypt:   0 ^ 9 ^ C:/programfiles/file.txt ^ 4 ^ 12 ^ 4 ^ 12
EX file-error:   ^!error ----------------
EX file-close:   ^!done

*/


////////////////////////////////////////////////////////////
// addMsg function to add message to vector<string> to output to file.
//
// arg1: Vector<string> to add line to.
// arg2: int fDone. Over all files done.
// arg3: int total. Total number of files.
// arg4: string path. File being de/encrypted, Current path.
// arg5: int bDone. Current blocks that have been done.
// arg6: int bTotal. Current, Total blocks that have been and need to be done.
// arg7: int bDoneSum. Overall blocks that have been done. 
// arg8: int bTotalSum. Overall, Total blocks that have been and need to be done.

int Control::addMsg(std::vector<std::string> &vec, int fDone, int total, std::string path, int bDone, int bTotal, int bDoneSum, int bTotalSum )
{ 

  if(vec == NULL) return 1;
  const int tmpSize=16;
  string ans="\0";
  char tmp[tmpSize]={'\0'};
  
  sprintf(tmp,"%i",fDone);
  ans.append(tmp);
  
  memset(tmp,0,tmpSize);
  sprintf(tmp," ^ %i ^ ",total);
  ans.append(tmp);
  
  ans.append(path);
  
  memset(tmp,0,tmpSize);
  sprintf(tmp," ^ %i ",bDone);
  ans.append(tmp);
  
  memset(tmp,0,tmpSize);
  sprintf(tmp," ^ %i ",bTotal);
  ans.append(tmp);
  
  memset(tmp,0,tmpSize);
  sprintf(tmp," ^ %i ",bDoneSum);
  ans.append(tmp);
  
  memset(tmp,0,tmpSize);
  sprintf(tmp," ^ %i ",bTotalSum);
  ans.append(tmp);
  
  vec.push_back(ans);
  return 0;
}// end add string function.



