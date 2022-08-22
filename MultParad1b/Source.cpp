#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <list>
using namespace std;


int main()
{
    ifstream infile;
    infile.open("infile.txt");
    int sheetsize = 45, currentsheet = 0, currentrow = 0;
    string text, word;
    map<string, list<int>> M;

    //Читання з файлу та відокремлення слів
read:
    if (getline(infile, text)) {

        stringstream textstr(text);
    readword:
        if (textstr >> word) {
            cout << endl << word;
            int i = 0;
            int wordsize = word.length();
        lowercaseloop:
            word[i] = tolower(word[i]);
            i++;
            if (i != wordsize)
                goto lowercaseloop;
            if (word != "in" && word != "on" && word != "of" && word != "for" && word != "the" && word != "not")
                if (M.find(word) == M.end()) {
                    M.insert(make_pair(word, 0));
                    M[word].push_back(currentsheet+1);
                }
                else {
                    if(find(M[word].begin(), M[word].end(), currentsheet + 1) == M[word].end())
                        M[word].push_back(currentsheet + 1);
                }


            goto readword;
        }
        currentrow++;
        if (currentrow == sheetsize) {
            currentsheet++;
            currentrow = 0;
            }

        goto read;
    }

    infile.close();
    ofstream outfile;
    outfile.open("outfile.txt");
    //Вивід
    auto it = M.begin();
    list<int>::iterator listit;
    if (M.size() == 0)
        goto end;
    
output:
    if ((*it).second.size() > 100)
    {
        it++;
        if (it != M.end())
            goto output;
        else
            goto end;
    }
    listit = (*it).second.begin();
    outfile << (*it).first << " - " << *listit;
    listit++;

    if (listit == (*it).second.end())
        goto listoutloopskip;

listoutloop:
    outfile <<", " << *listit;
    listit++;
    if (listit != (*it).second.end())
        goto listoutloop;
listoutloopskip:
    outfile << endl;;
    it++;
    
    if (it != M.end())
        goto output;

end:
    outfile.close();
    return 0;
}