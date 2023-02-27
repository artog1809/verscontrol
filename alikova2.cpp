#define _CRT_SECURE_NO_WARNINGS
//#include "documentation.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <map>
#include <iostream>

using namespace std;
using boost::property_tree::ptree;




vector<string> headerTag = { "h1", "h2", "h3", "h4", "h5", "h6" };

map<string, string> configureIndentOfTag(vector<string>& headerTag) {

    string cur = "";
    map<string, string> mp;
    for (auto str : headerTag) {
        mp[str] = cur;
        cur += "\t";
    }

    return mp;
}


template< typename T>
bool vectorContains(vector<T>& v, T item) {

    for (auto x : v) {
        if (x == item) {
            return true;
        }
    }

    return false;
}

void dfs(ptree propertyTree, vector<string>& headerTag, map<string, string>& mp, vector<string>& ans) {

    for (auto& v : propertyTree) {
        if (vectorContains(headerTag, v.first)) {
            ans.push_back(mp[v.first] + v.second.data());
        }

        //  cout << v.second.data() << "\n";
        dfs(v.second, headerTag, mp, ans);
    }
}


vector<string> getAllHeaders(string& html) {

    //Читаем XML
    ptree propertyTree;
    std::stringstream stream(html);
    boost::property_tree::read_xml(stream, propertyTree);

    map <string, string> mp = configureIndentOfTag(headerTag);
    vector<string> ans;
    dfs(propertyTree, headerTag, mp, ans);

    return ans;
}

int main(int argc, char* argv[])
{
    string html = "<ButtonList>\
	<h1>B1 <h2> cvk </h2> cvk </h1>\
	<h3>B2\</h3>\
	</ButtonList>";



    try {

        vector<string> ans = getAllHeaders(html);

        for (auto str : ans) {
            cout << str << "\n";
        }

    }
    catch (exception) {
        cout << "incorrect html\n";
    }



}





//int mainTmp(int argc, char* argv[])
//{
//    setlocale(LC_ALL, "Russian");
//
//    if (argc < 3) {
//        cerr << "Недостаточное количество аргументов";
//        return 0;
//    }
//
//    ifstream output_file(argv[2]);
//
//    //Если удалось открыть выходной файл
//
//
//
//    int Error_number = 0;
//
//    // Считать входные данные
//    Error_number = Read_text_from_file(argv[1]);
//
//    //Если при считывании была обнаружена ошибка
//    string error_text = "";
//    if (Error_number < 0)
//    {
//        switch (Error_number)
//        {
//        case -1:    //При считывании не удалось открыть входной файл
//            error_text = "Invalid input file specified. The file may not exist.";
//            break;
//        case -2:    //Расширение входного файла некорректно
//            error_text = "The file extension is incorrect. The file must have the extension .xml";
//            break;
//        case -3:    //Некорректный синтаксис
//            error_text = "The file can not be read. The input file may not have the correct syntax.";
//            break;
//        }
//
//        cerr << error_text;
//        return 0;
//    }
//
//    //Записать заголовки в выходной файл
//    Make_arr_string_and_find_headers(argv[1]);
//
//
//    return 0;
//}