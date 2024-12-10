#include<bits/stdc++.h>

int process_count = 0;
int in_sentence_cnt = 0;
int bracket_count = 0;
const std::wstring tab = L"    ";
std::map<int, std::map<std::wstring, std::deque<std::tuple<std::wstring, int, int>>>> Undeclared_Arrays;
std::map<std::wstring, std::deque<int>> pc;
std::vector<std::wstring> Arrays;
std::vector<std::wstring> output = {L"#coding: shift_jis\n\n#Template Zone\nfrom collections import defaultdict\n\ndef range(start :float, end :float, inc :float) -> list:\n    list = []\n    if inc > 0:\n        while start <= end:\n            list.append(start)\n            start = start + inc\n    else:\n        while start >= end:\n            list.append(start)\n            start = start + inc\n    return list\n\n#Your Translated Code Zone\n\n\n"};
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

    // std::string ord_to_string(ord order) {
    //     std::vector<std::string> s = {
    //         "PROCESS_END",
    //         "IF_A",
    //         "IF_B",
    //         "ELIF",
    //         "ELSE",
    //         "WHILE",
    //         "FOR_INCREASING",
    //         "FOR_DECREASING",
    //         "DECLARE_ARRAY",
    //         "VARIABLE",
    //         "PRINT"
    //     };
    //     return s[order];
    // }

    // UTF-8からワイド文字列に変換するヘルパー関数
    std::wstring utf8_to_wstring(const std::string &utf8) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(utf8);
    }

    // ワイド文字列からUTF-8文字列に変換するヘルパー関数
    std::string wstring_to_utf8(const std::wstring &wstr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }

    std::wstring remove_spaces(const std::wstring &sentence) {
        std::wstring close_id = L"";
        std::wstring ret = L"";
        int len = static_cast<int>(sentence.size());

        for (int i = 0; i < len; i++) {
            if (!close_id.empty()) {
                // 現在のクローズIDが設定されている場合
                ret.push_back(sentence[i]);
                if (sentence[i] == close_id.front()) {
                    close_id = L"";
                }
            } else {
                // 現在のクローズIDが設定されていない場合
                if (sentence[i] != L' ' && sentence[i] != L'　') { // 半角・全角スペースを除去
                    ret.push_back(sentence[i]);
                }
                if (sentence[i] == L'「') {
                    assert(close_id.empty());
                    close_id = L"」";
                }
                if (sentence[i] == L'”') {
                    assert(close_id.empty());
                    close_id = L"”";
                }
                if (sentence[i] == L'"') {
                    assert(close_id.empty());
                    close_id = L"\"";
                }
            }
        }

        return ret;
    }

    std::wstring make_it_half_size(const std::wstring &sentence) {
        std::wstring close_id = L"";
        std::wstring ret = L"";
        int len = static_cast<int>(sentence.size());

        // auto isnum = [](wchar_t wc) -> bool {
        //     return wc >= L'０' && wc <= L'９';
        // };

        auto apply = [&](std::wstring &str, wchar_t wc) -> void {
            switch (wc) {
                case L'←': str.push_back(L'='); break;
                case L'、': case L'，': str.push_back(L','); break;
                case L'「': str.push_back(L'"'); close_id = L"」"; break;
                case L'」': str.push_back(L'"'); break;
                case L'”': str.push_back(L'"'); close_id = L"”"; break;
                case L'＋': str.push_back(L'+'); break;
                case L'ー': str.push_back(L'-'); break;
                case L'×': str.push_back(L'*'); break;
                case L'÷': str.push_back(L'/'); break;
                case L'％': str.push_back(L'%'); break;
                case L'（': str.push_back(L'('); break;
                case L'）': str.push_back(L')'); break;
                case L'＝': str.push_back(L'='); break;
                case L'≠': str.push_back(L'!'); break;
                case L'＞': str.push_back(L'>'); break;
                case L'＜': str.push_back(L'<'); break;
                case L'≦': str.push_back(L'<'); break;
                case L'≧': str.push_back(L'>'); break;
                case L'０': case L'１': case L'２': case L'３': case L'４':
                case L'５': case L'６': case L'７': case L'８': case L'９':
                    str.push_back(wc - L'０' + L'0');
                    break;
                default: str.push_back(wc); break;
            }
        };

        for (int i = 0; i < len; i++) {
            wchar_t wc = sentence[i];

            if (!close_id.empty()) {
                // クローズIDが設定されている場合
                if (wc == close_id.front()) {
                    apply(ret, wc);
                    close_id.clear();
                }else {
                    ret.push_back(wc);
                }
            } else {
                // クローズIDが設定されていない場合
                if (wc == L'"') {
                    close_id = L"\"";
                    ret.push_back(wc);
                } else if (wc == L'=') {
                    ret += L"==";
                } else {
                    apply(ret, wc);
                }
            }
        }

        return ret;
    }

    std::wstring index_format(std::wstring sentence) {
        // 閉区間で渡す
        std::function<void(std::vector<std::wstring>&, int, int)> index_extend = [](std::vector<std::wstring>& s, int l, int r) -> void {
            std::wstring replace = L"";
            std::wstring now = L"";
            
            int left = l + 1;
            for (int i = l + 1; i < r; i++) {
                if (s[i] == L",") {
                    replace += L"[" + now + L"-1]";
                    now = L"";
                } else {
                    now += s[i];
                }
            }
            if (now.size() != 0) replace += L"[" + now + L"-1]";

            std::vector<std::wstring> new_s;
            for (int i = 0; i < l; i++) new_s.push_back(s[i]);
            new_s.push_back(replace);
            while (new_s.size() < r + 1) new_s.push_back(L"");
            for (int i = r + 1; i < s.size(); i++) new_s.push_back(s[i]);

            s = new_s;
            return;
        };

        int len = (int)sentence.size();

        {
            bool in_bracket = false;
            // 各配列の次元数の変更
            for (int i = 0; i < len; i++) {
                if (in_bracket) {
                    if (sentence[i] == L'"') in_bracket = false;
                } else {
                    if (sentence[i] == L'"') {
                        in_bracket = true;
                        continue;
                    }

                    for (std::wstring now : Arrays) {
                        if (i + now.size() < len && sentence[i + now.size()] == L'[' && sentence.substr(i, now.size()) == now) {
                            //[...[...]...]
                            int tot = 1;
                            int dim = 1;

                            for (int j = i + now.size() + 1; j < len; j++) {
                                if (sentence[j] == L'[') tot++;
                                if (sentence[j] == L']') tot--;
                                if (tot == 0) {
                                    break;
                                } else if (tot == 1 && sentence[j] == L',') {
                                    dim++;
                                }
                                assert(tot >= 0);
                            }

                            for (int k = 0; k < pc[now].size(); k++) {
                                std::get<2>(Undeclared_Arrays[pc[now][k]][now][k]) = std::max(dim, std::get<2>(Undeclared_Arrays[pc[now][k]][now][k]));
                            }
                        }
                    }
                }
            }
        }

        std::vector<std::wstring> words(len);
        for (int i = 0; i < len; i++) words[i].push_back(sentence[i]);

        bool in_bracket = false;
        std::stack<int> st;

        for (int i = 0; i < words.size(); i++) {
            if (in_bracket) {
                if (words[i].front() == L'"') in_bracket = false;
            } else {
                if (words[i].front() == L'"') {
                    in_bracket = true;
                }
                if (words[i] == L"[") {
                    st.push(i);
                }
                if (words[i] == L"]") {
                    index_extend(words, st.top(), i);
                    st.pop();
                }
            }
        }

        std::wstring ret = L"";
        for (std::wstring e : words) ret += e;

        return ret;
    }


    ord which_order(std::wstring sentence) {
        auto pref_eq = [](const std::wstring& str, const std::wstring& prefix) -> bool {
            return str.size() >= prefix.size() && str.substr(0, prefix.size()) == prefix;
        };

        auto suff_eq = [](const std::wstring& str, const std::wstring& suffix) -> bool {
            return str.size() >= suffix.size() && str.substr(str.size() - suffix.size()) == suffix;
        };

        if (sentence == L"を実行する" || sentence == L"を繰り返す") return PROCESS_END;

        if (pref_eq(sentence, L"もし")) {
            if (suff_eq(sentence, L"ならば"))  return IF_A;
            return IF_B;
        }

        if (pref_eq(sentence, L"を実行し,そうでなくもし")) return ELIF;
        if (pref_eq(sentence, L"を実行し,そうでなければ")) return ELSE;
        if (suff_eq(sentence, L"の間,")) return WHILE;
        if (suff_eq(sentence, L"増やしながら,")) return FOR_INCREASING;
        if (suff_eq(sentence, L"減らしながら,")) return FOR_DECREASING;
        if (suff_eq(sentence, L"を表示する")) return PRINT;
        if (suff_eq(sentence, L"にする")) return DECLARE_ARRAY;

        return VARIABLE;
    }

    class details {
    private:
        std::wstring unzip(std::vector<std::wstring> words) {
            std::wstring ret = L"";

            for (int i = 0; i < words.size(); i++) {
                ret = ret + words[i];
                if (i != words.size() - 1) ret.push_back(L' ');
            }

            return ret;
        }

        std::wstring unzip_bracket(std::vector<std::wstring> words) {
            std::vector<std::wstring> new_words;
            for (std::wstring s : words) {
                if (s != L"" && s != L" ") new_words.push_back(s);
            }
            std::wstring ret = L"";

            for (int i = 0; i < new_words.size(); i++) {
                if (new_words[i] == L"") {
                    continue;
                }
                ret = ret + new_words[i];
                if (i != new_words.size() - 1 && new_words[i] != L"(" && new_words[i + 1] != L")") ret.push_back(L' ');
            }

            return ret;
        }

        std::wstring f_conditional(std::wstring sentence) {
            std::function<bool(int, const std::wstring&)> substr_equal = 
                [&sentence](int i, const std::wstring& str) -> bool {
                    return i+str.size() <= sentence.size() && sentence.substr(i, str.size()) == str;
                };

            int len = (int)sentence.size();
            std::vector<std::wstring> words = {L"("};
            bool in_bracket = false;
            std::stack<int> brs;
            brs.push(0);

            for (int i = 0; i < len; i++) {
                if (in_bracket) {
                    words.back().push_back(sentence[i]);
                    if (sentence[i] == L'"') {
                        in_bracket = false;
                    }
                    continue;
                } else {
                    if (sentence[i] == L'(') {
                        brs.push(words.size() - 1);
                    } else if (sentence[i] == L')') {
                        brs.pop();
                    }

                    if (substr_equal(i, L"かつ")) {
                        if (words.back() == L"") words.pop_back();
                        words.push_back(L"and");
                        i += 1;
                        if (words.back() != L"") words.push_back(L"");
                    } else if (substr_equal(i, L"または")) {
                        if (words.back() == L"") words.pop_back();
                        words.push_back(L"or");
                        i += 2;
                        if (words.back() != L"") words.push_back(L"");
                    } else if (substr_equal(i, L"でない")) {
                        i += 2;
                        if (words.back() == L"") words.pop_back();
                        words.back().push_back(L')');
                        std::wstring tmp = L"";
                        tmp.push_back(words[brs.top()].front());
                        tmp = tmp + L"not(" + words[brs.top()].substr(1);
                        words[brs.top()] = tmp;
                    } else if (sentence[i] == L'"') {
                        in_bracket = true;
                        words.back().push_back(sentence[i]);
                    } else {
                        if (i < len - 1) {
                            std::wstring str = sentence.substr(i, 2);

                            if (str == L"<=" || str == L">=" || str == L"!=" || str == L"==") {
                                words.back() = words.back() + L" " + str + L" ";
                                i += 1;
                            } else {
                                words.back().push_back(sentence[i]);
                            }
                        } else {
                            words.back().push_back(sentence[i]);
                        }
                    }
                }
            }

            while (words.back() == L"") words.pop_back();
            words.front().erase(words.front().begin());

            std::vector<std::wstring> new_words;
            for (std::wstring s : words) {
                int left = 0;
                for (int i = 0; i < s.size(); i++) {
                    if (s[i] == L'(' || s[i] == L')') {
                        if (i - left != 0) new_words.push_back(s.substr(left, i - left));
                        new_words.push_back((s[i] == L'(' ? L"(" : L")"));
                        left = i + 1;
                    }
                }
                if (left != s.size()) new_words.push_back(s.substr(left));
            }

            swap(words, new_words);

            std::function<void(std::vector<std::wstring>&, int, int)> compress = 
                [&](std::vector<std::wstring>& s, int l, int r) -> void {
                    l++;
                    int top = l;
                    int blank = (int)(count(s.begin() + l, s.begin() + r, L""));
                    int cnt = 0;

                    if (r - l - blank >= 5) {
                        for (int i = l; i < r; i++) {
                            if (s[i] == L"") continue;

                            cnt++;
                            if (cnt > r - l - blank - 2) {
                                break;
                            }
                            if (cnt < 3) continue;

                            if (s[i] != L"and" && s[i] != L"or") {
                                s[i].push_back(L')');
                                s[top] = L"(" + s[top];
                            }
                        }
                    }

                    s[l - 1] = unzip_bracket(std::vector<std::wstring>(s.begin() + l - 1, s.begin() + r + 1));
                    for (int i = l; i <= r; i++) {
                        s[i] = L"";
                    }

                    return;
                };

            words.insert(words.begin(), L"(");
            words.push_back(L")");
            std::stack<int> st;
            int cnt = 0;

            for (int i = 0; i < words.size(); i++) {
                if (words[i] == L"(") {
                    st.push(i);
                } else if (words[i] == L")") {
                    int left = st.top();
                    st.pop();
                    // (left, i) 区間を圧縮
                    compress(words, left, i);
                }
            }

            std::wstring ret = unzip_bracket(words);
            return ret.substr(1, ret.size() - 2);
        }

        std::wstring f_PROCESS_END(std::wstring sentence) {
            std::function<void(std::wstring, std::wstring, int, int)> declare_array = [](std::wstring variable, std::wstring initial, int idx, int dim) -> void {
                std::wstring front = L"defaultdict(lambda : ";
                std::wstring ret = variable + L" = ";

                for(int i = 0; i < dim; i++) ret += front;

                ret += initial;

                for(int i = 0; i < dim; i++) ret.push_back(')');

                for(int i = 0; i < process_count; i++) ret = tab + ret;

                output[idx] = ret;

                return;
            };

            std::vector<std::wstring> vec;

            for(auto e : Undeclared_Arrays[process_count]) {
                for(auto f : e.second) {
                    declare_array(e.first, std::get<0>(f), std::get<1>(f), std::get<2>(f));
                    vec.push_back(e.first);
                }
            }
            for(std::wstring s : vec) {
                Undeclared_Arrays[process_count].erase(s);
                pc.erase(s);
                Arrays.erase(find(Arrays.begin(), Arrays.end(), s));
            }
            return L"";
        }

        std::wstring f_IF_A(std::wstring sentence) {
            int len = (int)sentence.size();
            std::vector<std::wstring> words;

            words.push_back(L"if");
            words.push_back(f_conditional(sentence.substr(2, len - 5))); // もしならばの部分を除く
            words.push_back(L":");

            return unzip(words);
        }

        std::wstring f_IF_B(std::wstring sentence) {
            int len = (int)sentence.size();
            bool in_bracket = false;
            int seg;
            for (int i = 0; i < len - 2; i++) {
                if (!in_bracket && sentence.substr(i, 3) == L"ならば") {
                    seg = i + 3;
                    break;
                }
                if (sentence[i] == L'"') {
                    in_bracket = true ^ in_bracket;
                }
            }
            
            translator next_solver;

            return f_IF_A(sentence.substr(0, seg)) + L"\n" + next_solver.analysis(sentence.substr(seg), true);
        }


        std::wstring f_ELIF(std::wstring sentence) {
            int len = (int)sentence.size();
            std::vector<std::wstring> words;

            words.push_back(L"elif");
            words.push_back(f_conditional(sentence.substr(12, len - 15))); // を実行し,そうでなくもし ... ならば　の部分を除く
            words.push_back(L":");

            return unzip(words);
        }


        std::wstring f_ELSE(std::wstring sentence) {
            return L"else :";
        }

        std::wstring f_WHILE(std::wstring sentence) {
            int len = (int)sentence.size();
            return L"while " + f_conditional(sentence.substr(0, len - 3)) + L" :"; // の間, の部分を除く
        }

        std::wstring f_FOR_INCREASING(std::wstring sentence) {
            std::function<bool(int, const std::wstring&)> substr_equal = 
                [&sentence](int i, const std::wstring& str) -> bool {
                    return i+str.size() <= sentence.size() && sentence.substr(i, str.size()) == str;
                };

            int len = (int)sentence.size();
            std::wstring variable, initial, finish, plus;
            int left = 0;
            for(int i = 0; i < len; i++) {
                if(i <= left) continue;

                if(sentence[i] == L'を') {
                    variable = sentence.substr(left, i-left);
                    left = i+1;
                }
                if(substr_equal(i, L"から")) {
                    initial = sentence.substr(left, i-left);
                    left = i+2;
                }
                if(substr_equal(i, L"まで")) {
                    finish = sentence.substr(left, i-left);
                    left = i+2;
                }
                if(substr_equal(i, L"ずつ増やしながら,")) {
                    plus = sentence.substr(left, i-left);
                    left = i+9;
                }
            }

            std::wstring range_expression = L"range(" + initial + L", " + finish + L", " + plus + L")";

            return unzip({L"for", variable, L"in", range_expression, L":"});
        }

        std::wstring f_FOR_DECREASING(std::wstring sentence) {
            std::function<bool(int, const std::wstring&)> substr_equal = 
                [&sentence](int i, const std::wstring& str) -> bool {
                    return i+str.size() <= sentence.size() && sentence.substr(i, str.size()) == str;
                };

            int len = (int)sentence.size();
            std::wstring variable, initial, finish, plus;
            int left = 0;
            for(int i = 0; i < len; i++) {
                if(i <= left) continue;

                if(sentence[i] == L'を') {
                    variable = sentence.substr(left, i-left);
                    left = i+1;
                }
                if(substr_equal(i, L"から")) {
                    initial = sentence.substr(left, i-left);
                    left = i+2;
                }
                if(substr_equal(i, L"まで")) {
                    finish = sentence.substr(left, i-left);
                    left = i+2;
                }
                if(substr_equal(i, L"ずつ減らしながら,")) {
                    plus = sentence.substr(left, i-left);
                    left = i+9;
                }
            }

            std::wstring range_expression = L"range(" + initial + L", " + finish + L", -(" + plus + L"))";

            return unzip({L"for", variable, L"in", range_expression, L":"});
        }

        std::wstring f_DECLARE_ARRAY(std::wstring sentence) {
            int len = (int)sentence.size();
            std::wstring variable;
            std::wstring initial;

            for(int i = 0; i < len; i++) {
                if(sentence.substr(i, 7) == L"のすべての値を") {
                    variable = sentence.substr(0, i);
                    initial = sentence.substr(i+7, len-(i+7)-3); // にする の部分を除く
                    break;
                }
            }

            Undeclared_Arrays[process_count][variable].push_back(make_tuple(initial, id, 1));
            pc[variable].push_back(process_count);
            Arrays.push_back(variable);
            return L"";
        }

        std::wstring f_VARIABLE(std::wstring sentence) {
            int len = (int)sentence.size();
            bool in_string = false;
            std::wstring ret = L"";

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
                        ret += L"\n";
                        for(int j = 0; j < process_count; j++) ret += tab;
                    }else {
                        ret.push_back(sentence[i]);
                    }
                }
            }
            return ret;
        }

        std::wstring f_PRINT(std::wstring sentence) {
            sentence = sentence.substr(0, (int)sentence.size()-5) + L"と";
            int len = (int)sentence.size();
            std::vector<std::wstring> words;
            
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

                if(sentence[i] == L'と') {
                    words.push_back(sentence.substr(left, i-left) + L",");
                    left = i+1;
                }else if(sentence[i] == '"') {
                    in_bracket = false;
                }
            }
            
            words.back().pop_back();
            return L"print(" + unzip(words) + L", sep='', end='\\n')";
        }
    public:
        std::wstring detail_analysis(std::wstring sentence, ord order) {
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
            return L""; 
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
    std::wstring analysis(std::wstring sentence, bool ignore = false) {
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

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << " " << " <output file>" << std::endl;
        return 1;
    }

    // std::wifstreamを使用してUTF-8でファイルを開く
    std::string input_filepath = argv[1];
    std::wifstream file(input_filepath);

    if(!file.is_open()) {
        std::cerr << "Error: Could not open file " << input_filepath << std::endl;
        return 1;
    }

    file.imbue(std::locale("ja_JP.UTF-8"));  // 日本語ロケールを設定
    
    std::vector<std::wstring> lines;
    std::wstring line;

    std::wcerr << L"Start Reading the Original Text" << std::endl;

    // ファイルから1行ずつ読み込み
    while (getline(file, line)) {
        lines.push_back(line);
    }

    lines.push_back(L"を実行する");

    std::wcerr << L"Finish Reading the Original Text" << std::endl;

    translator solver;

    for(const std::wstring i : lines) {
        std::wstring new_line = solver.analysis(i);
        output.push_back(new_line);
        id++;
    }

    std::wcerr << L"Start Writing the Translated Text" << std::endl;

    std::string output_filepath = argv[2];
    std::wofstream output_file(output_filepath);

    if(!output_file.is_open()) {
        std::cerr << "Error: Could not open file " << output_filepath << std::endl;
        return 1;
    }

    output_file.imbue(std::locale("ja_JP.UTF-8"));  // 日本語ロケールを設定

    for(const std::wstring i : output) {
        output_file << i << std::endl;
    }

    std::wcerr << L"Finish Writing the Translated Text" << std::endl;
    return 0;
}
