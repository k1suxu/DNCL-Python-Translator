#include<bits/stdc++.h>
#include<Windows.h>
using namespace std;

int process_count = 0;
int in_sentence_cnt = 0;
int bracket_count = 0;
const string tab = "    ";
map<int, map<string, deque<tuple<string, int, int>>>> Undeclared_Arrays;
map<string, deque<int>> pc;
vector<string> Arrays;
vector<string> output = {"#coding: shift_jis\n\n#Template Zone\nfrom collections import defaultdict\n\ndef range(start :float, end :float, inc :float) -> list:\n    list = []\n    if inc > 0:\n        while start <= end:\n            list.append(start)\n            start = start + inc\n    else:\n        while start >= end:\n            list.append(start)\n            start = start + inc\n    return list\n\n#Your Translated Code Zone\n\n\n"};
int id = 1;

class translator {
private:
    enum ord {
        PROCESS_END,
        IF_A,
        IF_B,
        ELIF,
        ELSE,
        WHILE,
        FOR_INCREASING,
        FOR_DECREASING,
        DECLARE_ARRAY,
        VARIABLE,
        PRINT
    };

    string ord_to_string(ord order) {
        vector<string> s = {
            "PROCESS_END",
            "IF_A",
            "IF_B",
            "ELIF",
            "ELSE",
            "WHILE",
            "FOR_INCREASING",
            "FOR_DECREASING",
            "DECLARE_ARRAY",
            "VARIABLE",
            "PRINT"
        };
        return s[order];
    }

    string remove_spaces(string sentence) {
        string close_id = "";
        string ret = "";
        int len = (int)sentence.size();
        bool skip = false;

        for(int i = 0; i < len; i++) {
            if(skip) {
                skip = false;
                continue;
            }

            if(close_id != "") {
                if(IsDBCSLeadByte(sentence[i])) {
                    skip = true;
                    assert(i < len-1);
                    string double_byte = sentence.substr(i, 2);

                    ret = ret + double_byte;
                    if(close_id.size() == 2 && double_byte == close_id) {
                        close_id = "";
                    }
                }else {
                    ret.push_back(sentence[i]);
                    if(close_id.size() == 1 && sentence[i] == close_id.front()) {
                        close_id = "";
                    }
                }
            }else {
                if(IsDBCSLeadByte(sentence[i])) {
                    skip = true;
                    assert(i < len-1);
                    string double_byte = sentence.substr(i, 2);

                    if(double_byte != "　") {
                        ret = ret + double_byte;
                    }
                    if(double_byte == "「") {
                        assert(close_id.size() == 0);
                        close_id = "」";
                    }
                    if(double_byte == "”") {
                        assert(close_id.size() == 0);
                        close_id = "”";
                    }
                }else {
                    if(sentence[i] != ' ') {
                        ret.push_back(sentence[i]);
                    }
                    if(sentence[i] == '"') {
                        assert(close_id.size() == 0);
                        close_id.push_back('"');
                    }
                }
            }
        }

        return ret;
    }

    string make_it_half_size(string sentence) {

        string close_id = "";

        function<bool(string)> isnum = [](string double_byte) -> bool {
            if(double_byte == "０") return true;
            if(double_byte == "１") return true;
            if(double_byte == "２") return true;
            if(double_byte == "３") return true;
            if(double_byte == "４") return true;
            if(double_byte == "５") return true;
            if(double_byte == "６") return true;
            if(double_byte == "７") return true;
            if(double_byte == "８") return true;
            if(double_byte == "９") return true;

            return false;
        };

        function<void(string&, string)> apply = [&](string& str, string double_byte) -> void {
            if(double_byte == "←") str.push_back('=');
            else if(double_byte == "、") str.push_back(',');
            else if(double_byte == "，") str.push_back(',');
            else if(double_byte == "「") str.push_back('"'), close_id = "」";
            else if(double_byte == "」") str.push_back('"');
            else if(double_byte == "”") str.push_back('"'), close_id = "”";
            else if(double_byte == "＋") str.push_back('+');
            else if(double_byte == "ー") str.push_back('-');
            else if(double_byte == "×") str.push_back('*');
            else if(double_byte == "÷") str = str + "//";
            else if(double_byte == "/") str.push_back('/');
            else if(double_byte == "％") str.push_back('%');
            else if(double_byte == "（") str.push_back('(');
            else if(double_byte == "）") str.push_back(')');
            else if(double_byte == "＝") str = str + "==";
            else if(double_byte == "≠") str = str + "!=";
            else if(double_byte == "＞") str.push_back('>');
            else if(double_byte == "＜") str.push_back('<');
            else if(double_byte == "≦") str = str + "<=";
            else if(double_byte == "≧") str = str + ">=";
            else if(double_byte == "０") str.push_back('0');
            else if(double_byte == "１") str.push_back('1');
            else if(double_byte == "２") str.push_back('2');
            else if(double_byte == "３") str.push_back('3');
            else if(double_byte == "４") str.push_back('4');
            else if(double_byte == "５") str.push_back('5');
            else if(double_byte == "６") str.push_back('6');
            else if(double_byte == "７") str.push_back('7');
            else if(double_byte == "８") str.push_back('8');
            else if(double_byte == "９") str.push_back('9');
            else str = str + double_byte;
        };
        
        int len = sentence.size();
        string ret = "";
        bool skip = false;

        for(int i = 0; i < len; i++) {
            if(skip) {
                skip = false;
                continue;
            }

            if(close_id != "") {
                if(IsDBCSLeadByte(sentence[i]) == 0) {
                    if(close_id.size() == 1 && sentence[i] == close_id.front()) {
                        close_id = "";
                    }
                    ret.push_back(sentence[i]);
                }else {
                    skip = true;
                    string double_byte = sentence.substr(i, 2);

                    if(close_id.size() == 2 && double_byte == close_id) {
                        close_id = "";
                        ret.push_back('"');
                    }else {
                        ret = ret + double_byte;
                    }
                }
            }else {
                if(IsDBCSLeadByte(sentence[i]) == 0) {
                    if(sentence[i] == '"') {
                        assert(close_id.size() == 0);
                        close_id.push_back(sentence[i]);
                    }
                    if(sentence[i] == '=') ret = ret + "==";
                    else ret.push_back(sentence[i]);
                }else {
                    skip = true;
        
                    string double_byte = sentence.substr(i, 2);
                    apply(ret, double_byte);
                }
            }
        }

        return ret;
    }

    string index_format(string sentence) {
        //閉区間で渡す
        function<void(vector<string>&, int, int)> index_extend = [](vector<string>& s, int l, int r) -> void {
            string replace = "";
            string now = "";
            
            int left = l+1;
            for(int i = l+1; i < r; i++) {
                if(s[i] == ",") {
                    replace += "[" + now + "-1]";
                    now = "";
                }else {
                    now += s[i];
                }
            }
            if(now.size() != 0) replace += "[" + now + "-1]";

            vector<string> new_s;
            for(int i = 0; i < l; i++) new_s.push_back(s[i]);
            new_s.push_back(replace);
            while(new_s.size() < r+1) new_s.push_back("");
            for(int i = r+1; i < s.size(); i++) new_s.push_back(s[i]);

            s = new_s;

            return;
        };

        int len = (int)sentence.size();

        {
            bool in_bracket = false;
            //各配列の次元数の変更
            for(int i = 0; i < len; i++) {
                if(in_bracket) {
                    if(sentence[i] == '"') in_bracket = false;
                }else {
                    if(sentence[i] == '"') {
                        in_bracket = true;
                        continue;
                    }

                    for(string now : Arrays) {
                        if(i+now.size() < len && sentence[i+now.size()] == '[' && sentence.substr(i, now.size()) == now) {
                            //[...[...]...]
                            int tot = 1;
                            int dim = 1;

                            for(int j = i+now.size()+1; j < len; j++) {
                                if(sentence[j] == '[') tot++;
                                if(sentence[j] == ']') tot--;
                                if(tot == 0) {
                                    break;
                                }else if(tot == 1 && sentence[j] == ',') {
                                    dim++;
                                }
                                assert(tot >= 0);
                            }

                            for(int k = 0; k < pc[now].size(); k++) {
                                get<2>(Undeclared_Arrays[pc[now][k]][now][k]) = max(dim, get<2>(Undeclared_Arrays[pc[now][k]][now][k]));
                            }
                        }
                    }
                }
            }
        }

        vector<string> words(len);
        for(int i = 0; i < len; i++) words[i].push_back(sentence[i]);

        bool in_bracket = false;
        stack<int> st;

        for(int i = 0; i < words.size(); i++) {
            if(in_bracket) {
                if(words[i].front() == '"') in_bracket = false;
            }else {
                if(words[i].front() == '"') {
                    in_bracket = true;
                }
                if(words[i] == "[") {
                    st.push(i);
                }
                if(words[i] == "]") {
                    index_extend(words, st.top(), i);
                    st.pop();
                }
            }
        }

        string ret = "";
        for(string e : words) ret += e;

        return ret;
    }

    ord which_order(string sentence) {
        if(sentence == "を実行する" || sentence == "を繰り返す") {
            return PROCESS_END;
        }

        if(sentence.size() >= 4 && sentence.substr(0, 4) == "もし") {
            if(sentence.substr(sentence.length() - 6) == "ならば") {
                return IF_A;
            }else {
                return IF_B;
            }
        }

        if(sentence.size() >= 23 && sentence.substr(0, 23) == "を実行し,そうでなくもし") {
            return ELIF;
        }

        if(sentence.size() >= 23 && sentence.substr(0, 23) == "を実行し,そうでなければ") {
            return ELSE;
        }

        if(sentence.size() >= 5 && sentence.substr(sentence.length() - 5) == "の間,") {
            return WHILE;
        }

        if(sentence.size() >= 13 && sentence.substr(sentence.length() - 13) == "増やしながら,") {
            return FOR_INCREASING;
        }

        if(sentence.size() >= 13 && sentence.substr(sentence.length() - 13) == "減らしながら,") {
            return FOR_DECREASING;
        }

        if(sentence.size() >= 10 && sentence.substr(sentence.length() - 10) == "を表\示する") {
            return PRINT;
        }

        if(sentence.size() >= 6 && sentence.substr(sentence.length() - 6) == "にする") {
            return DECLARE_ARRAY;
        }

        return VARIABLE;
    }

    class details {
    private:
        string unzip(vector<string> words) {
            string ret = "";

            for(int i = 0; i < words.size(); i++) {
                ret = ret + words[i];
                if(i != words.size() - 1) ret.push_back(' ');
            }

            return ret;
        }
        string unzip_bracket(vector<string> words) {
            vector<string> new_words;
            for(string s : words) {
                if(s != "" && s != " " ) new_words.push_back(s);
            }
            string ret = "";

            for(int i = 0; i < new_words.size(); i++) {
                if(new_words[i] == "") {
                    continue;
                }
                ret = ret + new_words[i];
                if(i != new_words.size() - 1 && new_words[i] != "(" && new_words[i + 1] != ")") ret.push_back(' ');
            }

            return ret;
        }

        string  f_conditional(string sentence) {
            int len = (int)sentence.size();
            vector<string> words = {"("};
            bool in_bracket = false;
            stack<int> brs;
            brs.push(0);

            for(int i = 0; i < len; i++) {
                if(in_bracket) {
                    words.back().push_back(sentence[i]);
                    if(sentence[i] == '"') {
                        in_bracket = false;
                    }
                    continue;
                }else {
                    if(sentence[i] == '(') {
                        brs.push(words.size() - 1);
                    }else if(sentence[i] == ')') {
                        brs.pop();
                    }

                    if(i < len - 3 && sentence.substr(i, 4) == "かつ") {
                        if(words.back() == "") words.pop_back();
                        words.push_back("and");
                        i += 3;
                        if(words.back() != "") words.push_back("");
                    }else if(i < len - 5 && sentence.substr(i, 6) == "または") {
                        if(words.back() == "") words.pop_back();
                        words.push_back("or");
                        i += 5;
                        if(words.back() != "") words.push_back("");
                    }else if(i < len - 5 && sentence.substr(i, 6) == "でない") {
                        i += 5;
                        if(words.back() == "") words.pop_back();
                        words.back().push_back(')');
                        string tmp = "";
                        tmp.push_back(words[brs.top()].front());
                        tmp = tmp + "not(" + words[brs.top()].substr(1);
                        words[brs.top()] = tmp;
                    }else if(sentence[i] == '"') {
                        in_bracket = true;
                        words.back().push_back(sentence[i]);
                    }else {
                        if(i < len - 1) {
                            string str = sentence.substr(i, 2);
                            
                            if(str == "<=" || str == ">=" || str == "!=" || str == "==") {
                                words.back() = words.back() + " " + str + " ";
                                i++;
                            }else {
                                words.back().push_back(sentence[i]);
                            }
                        }else {
                            words.back().push_back(sentence[i]);
                        }
                    }
                }
            }

            while(words.back() == "") words.pop_back();
            words.front().erase(words.front().begin());

            vector<string> new_words;
            for(string s : words) {
                int left = 0;
                for(int i = 0; i < s.size(); i++) {
                    if(s[i] == '(' || s[i] == ')') {
                        if(i - left != 0) new_words.push_back(s.substr(left, i-left));
                        new_words.push_back((s[i] == '('? "(" : ")"));
                        left = i+1;
                    }
                }
                if(left != s.size()) new_words.push_back(s.substr(left));
            }

            swap(words, new_words);

            function<void(vector<string>&, int, int)> compress = [&](vector<string>& s, int l, int r) -> void {
                l++;
                int top = l;
                int blank = (int)(count(s.begin() + l, s.begin() + r, ""));
                int cnt = 0;

                if(r - l - blank >= 5) {
                    for(int i = l; i < r; i++) {
                        if(s[i] == "") continue;

                        cnt++;
                        if(cnt > r - l - blank - 2) {
                            break;
                        }
                        if(cnt < 3) continue;

                        if(s[i] != "and" && s[i] != "or") {
                            s[i].push_back(')');
                            s[top] = '(' + s[top];
                        }
                    }
                }

                s[l-1] = unzip_bracket(vector<string>(s.begin() + l-1, s.begin() + r+1));
                for(int i = l; i <= r; i++) {
                    s[i] = "";
                }

                return;
            };

            words.insert(words.begin(), "(");
            words.push_back(")");
            stack<int> st;
            int cnt = 0;

            for(int i = 0; i < words.size(); i++) {
                if(words[i] == "(") {
                    st.push(i);
                }else if(words[i] == ")") {
                    int left = st.top();
                    st.pop();
                    //(left, i)区間を圧縮
                    compress(words, left, i);
                }
            }

            string ret = unzip_bracket(words);
            return ret.substr(1, ret.size() - 2);
        }

        string f_PROCESS_END(string sentence) {
            auto declare_array = [](string variable, string initial, int idx, int dim) -> void {
                string front = "defaultdict(lambda : ";
                string ret = variable + " = ";

                for(int i = 0; i < dim; i++) ret += front;

                ret += initial;

                for(int i = 0; i < dim; i++) ret.push_back(')');

                for(int i = 0; i < process_count; i++) ret = tab + ret;

                output[idx] = ret;

                return;
            };

            vector<string> vec;

            for(auto e : Undeclared_Arrays[process_count]) {
                for(auto f : e.second) {
                    declare_array(e.first, get<0>(f), get<1>(f), get<2>(f));
                    vec.push_back(e.first);
                }
            }
            for(string s : vec) {
                Undeclared_Arrays[process_count].erase(s);
                pc.erase(s);
                Arrays.erase(find(Arrays.begin(), Arrays.end(), s));
            }
            return "";
        }

        string f_IF_A(string sentence) {
            int len = (int)sentence.size();
            vector<string> words;

            words.push_back("if");
            words.push_back(f_conditional(sentence.substr(4, len - 10)));
            words.push_back(":");

            return unzip(words);
        }

        string f_IF_B(string sentence) {
            int len = (int)sentence.size();
            bool in_bracket = false;
            int seg;
            for(int i = 0; i < len - 5; i++) {
                if(!in_bracket && sentence.substr(i, 6) == "ならば") {
                    seg = i + 6;
                    break;
                }
                if(sentence[i] == '"') {
                    in_bracket = true ^ in_bracket;
                }
            }
            
            translator next_solver;

            return f_IF_A(sentence.substr(0, seg)) + "\n" + next_solver.analysis(sentence.substr(seg), true);
        }

        string f_ELIF(string sentence) {
            int len = (int)sentence.size();
            vector<string> words;

            words.push_back("elif");
            words.push_back(f_conditional(sentence.substr(23, len - 29)));
            words.push_back(":");

            return unzip(words);
        }

        string f_ELSE(string sentence) {
            return "else :";
        }

        string f_WHILE(string sentence) {
            int len = (int)sentence.size();
            return "while " + f_conditional(sentence.substr(0, len - 5)) + " :";
        }

        string f_FOR_INCREASING(string sentence) {
            int len = (int)sentence.size();
            string variable, initial, finish, plus;
            int left = 0;
            for(int i = 0; i < len; i++) {
                if(i <= left) continue;

                if(i <= len-2 && sentence.substr(i, 2) == "を") {
                    variable = sentence.substr(left, i-left);
                    left = i+2;
                }
                if(i <= len-4 && sentence.substr(i, 4) == "から") {
                    initial = sentence.substr(left, i-left);
                    left = i+4;
                }
                if(i <= len-4 && sentence.substr(i, 4) == "まで") {
                    finish = sentence.substr(left, i-left);
                    left = i+4;
                }
                if(i <= len-17 && sentence.substr(i, 17) == "ずつ増やしながら,") {
                    plus = sentence.substr(left, i-left);
                    left = i+17;
                }
            }

            string range_expression = "range(" + initial + ", " + finish + ", " + plus + ")";

            return unzip({"for", variable, "in", range_expression, ":"});
        }

        string f_FOR_DECREASING(string sentence) {
            int len = (int)sentence.size();
            string variable, initial, finish, plus;
            int left = 0;
            for(int i = 0; i < len; i++) {
                if(i <= left) continue;

                if(i <= len-2 && sentence.substr(i, 2) == "を") {
                    variable = sentence.substr(left, i-left);
                    left = i+2;
                }
                if(i <= len-4 && sentence.substr(i, 4) == "から") {
                    initial = sentence.substr(left, i-left);
                    left = i+4;
                }
                if(i <= len-4 && sentence.substr(i, 4) == "まで") {
                    finish = sentence.substr(left, i-left);
                    left = i+4;
                }
                if(i <= len-17 && sentence.substr(i, 17) == "ずつ減らしながら,") {
                    plus = sentence.substr(left, i-left);
                    left = i+17;
                }
            }

            string range_expression = "range(" + initial + ", " + finish + ", -(" + plus + "))";

            return unzip({"for", variable, "in", range_expression, ":"});
        }

        string f_DECLARE_ARRAY(string sentence) {
            int len = (int)sentence.size();
            string variable;
            string initial;

            for(int i = 0; i < len; i++) {
                if(sentence.substr(i, 14) == "のすべての値を") {
                    variable = sentence.substr(0, i);
                    initial = sentence.substr(i+14, len-(i+14)-6);
                    break;
                }
            }

            Undeclared_Arrays[process_count][variable].push_back(make_tuple(initial, id, 1));
            pc[variable].push_back(process_count);
            Arrays.push_back(variable);
            return "";
        }

        string f_VARIABLE(string sentence) {
            int len = (int)sentence.size();
            bool in_string;
            string ret = "";

            for(int i = 0; i < len; i++) {
                if(in_string) {
                    if(sentence[i] == '"') in_string = false;
                    ret.push_back(sentence[i]);
                }else {
                    if(sentence[i] == '{') {
                        sentence[i] = '[';
                        bracket_count++;
                    }
                    if(sentence[i] == '}') {
                        sentence[i] = ']';
                        bracket_count--;
                    }
                    if(sentence[i] == ',' && bracket_count == 0) {
                        ret += "\n";
                        for(int j = 0; j < process_count; j++) ret += tab;
                    }else {
                        ret.push_back(sentence[i]);
                    }
                }
            }
            return ret;
        }

        string f_PRINT(string sentence) {
            sentence = sentence.substr(0, (int)sentence.size()-10) + "と";
            int len = (int)sentence.size();
            vector<string> words;
            
            bool in_bracket = false;
            int left = 0;

            for(int i = 0; i < len; i++) {
                if(i < left) continue;

                if(in_bracket) {
                    if(sentence[i] == '"') {
                        in_bracket = false;
                    }

                    continue;
                }

                if(IsDBCSLeadByte(sentence[i])) {
                    if(sentence.substr(i, 2) == "と") {
                        words.push_back(sentence.substr(left, i-left) + ",");
                        left = i+2;
                    }
                }else if(sentence[i] == '"') {
                    in_bracket = true;
                }
            }
            
            words.back().pop_back();
            return "print(" + unzip(words) + ", sep='', end='\\n')";
        }
    public:
        string detail_analysis(string sentence, ord order) {
            switch(order) {
                case PROCESS_END:
                    return f_PROCESS_END(sentence);
                break;
                case IF_A:
                    return f_IF_A(sentence);
                break;
                case IF_B:
                    return f_IF_B(sentence);
                break;
                case ELIF:
                    return f_ELIF(sentence);
                break;
                case ELSE:
                    return f_ELSE(sentence);
                break;
                case WHILE:
                    return f_WHILE(sentence);
                break;
                case FOR_INCREASING:
                    return f_FOR_INCREASING(sentence);
                break;
                case FOR_DECREASING:
                    return f_FOR_DECREASING(sentence);
                break;
                case DECLARE_ARRAY:
                    return f_DECLARE_ARRAY(sentence);
                break;
                case VARIABLE:
                    return f_VARIABLE(sentence);
                break;
                case PRINT:
                    return f_PRINT(sentence);
                break;
            }

            assert(false);
            return ""; 
        }
    };

    void process_count_change(ord order) {
        switch(order) {
            case PROCESS_END:
                process_count--;
            break;
            case IF_A:
                process_count++;
            break;
            case IF_B:
            break;
            case ELIF:
            break;
            case ELSE:
            break;
            case WHILE:
                process_count++;
            break;
            case FOR_INCREASING:
                process_count++;
            break;
            case FOR_DECREASING:
                process_count++;
            break;
            case DECLARE_ARRAY:
            break;
            case VARIABLE:
            break;
            case PRINT:
            break;

            default:
                assert(false);
            break;
        }

        return;
    }

public:
    string analysis(string sentence, bool ignore = false) {
        if(!ignore) in_sentence_cnt = 0;
        else in_sentence_cnt++;

        details dt;
        //format
        if(!ignore) {
            if(sentence.size() == 0) return sentence;
            sentence = remove_spaces(sentence);
            if(sentence.size() == 0) return sentence;   
            sentence = make_it_half_size(sentence);
            sentence = index_format(sentence);
        }

        //divide
        ord order = which_order(sentence);
        
        //detail
        sentence = dt.detail_analysis(sentence, order);

        int minus = (order == ELIF || order == ELSE);

        for(int i = 0; i < process_count - minus + in_sentence_cnt; i++) {
            sentence = tab + sentence;
        }

        if(!ignore) {
            process_count_change(order);
        }

        if(ignore) in_sentence_cnt--;

        return sentence;
    }
};

int main() {
    string input_filename = "";//入力データへのパス

    vector<string> lines;
    string line;

    ifstream input_file(input_filename);
    if(!input_file.is_open()) {
        cerr << "Failed to open - " << input_filename << endl;
        return 0;
    }

    cout << "Start Reading the Original Text" << endl;

    while(true) {
        getline(input_file, line);
        if(line == "FINISH CODE") break;
        lines.push_back(line);
    }

    lines.push_back("を実行する");

    input_file.close();

    cout << "Finish Reading the Original Text" << endl;

    translator solver;

    for(const string i : lines) {
        string new_line = solver.analysis(i);
        output.push_back(new_line);
        id++;
    }

    string output_filename = "";//出力用ファイルへのパス
    fstream file_out;

    file_out.open(output_filename, std::ios_base::out);
    if(!file_out.is_open()) {
        cerr << "Failed to open - " << output_filename << endl;
        return 0;
    }else {
        cout << "Start Writing the Translated Text" << endl;

        for(const auto &i : output) {
            file_out << i << endl;
        }

        cout << "Finish Writing the Translated Text" << endl;
    }
    return 0;
}
