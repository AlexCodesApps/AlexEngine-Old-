#pragma once
#include <cstddef>
#include <iostream>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>
#include <sstream>
#include <ostream>
#include <fstream>

namespace MetaTile {
    struct TextureData {
        using Coords = std::pair<size_t, size_t>;
        std::string Name;
        std::string Asset;
        size_t tilewidth;
        size_t tileoffset;
        std::unordered_map<size_t, Coords> CoordsMap;
    };
    struct TilemapData {
        std::string Name;
        std::string TextureDataName;
        size_t w;
        size_t h;
        std::vector<size_t> data;
    };

    using FlagData = std::string;

    struct FlagAttribData {
        std::string TextureName;
        FlagData Flag;
        size_t Id;
    };

    using StrVec = std::vector<std::string>;
    inline StrVec Tokenizer(std::string_view str) {
        bool str_mode = false;
        bool word_mode = false;
        StrVec strs;
        auto tracker_pos = str.begin();
        for (auto i = tracker_pos; i < str.end()+1; i++) {
            auto end_word_mode = [&](auto t) {
                word_mode = false;
                strs.emplace_back(tracker_pos, t);
                tracker_pos = t;
            };
            auto end_str_mode = [&]() {
                str_mode = false;
                strs.emplace_back(tracker_pos, i+1);
                tracker_pos = i+1;
            };
            auto unary_mode = [&]() {
                strs.emplace_back(i, 1);
                tracker_pos = i+1;
            };
            if (i == str.end()) {
                if (word_mode) end_word_mode(i);
                if (str_mode) end_str_mode();
                break;
            }
            auto c = *i;
            if (str_mode) {
                if (c == '\"') {
                    end_str_mode();
                }
                continue;
            }
            switch (c) {
            case '[':
            case ']':
            case ',':
            case '\n':
            case '#':
            case '=':
                if (word_mode) {
                    end_word_mode(i);
                }
                unary_mode();
                continue;
            case '\"':
                str_mode = true;
                tracker_pos = i;
                continue;
            }
            if (std::isspace(c)) {
                if (word_mode)
                    end_word_mode((i));
                continue;
            }
            if (!word_mode) {
                tracker_pos = i;
                word_mode = true;
            }
            if (i + 1 == str.end()) {
                if (str_mode) end_str_mode();
                else end_word_mode(i+1);
            }
        }
        return strs;
    };

    inline StrVec StripComments(const StrVec& Old) {
        StrVec Vec;
        bool hitComment = false;
        for (auto& str : Old) {
            if (str == "#") {
                hitComment = true;
                continue;
            }
            else if (hitComment) {
                if (str == "\n") hitComment = false;
                continue;
            }
            if (str == "\n") continue;
            Vec.push_back(str);
        }
        return Vec;
    };

    using Parsed_Elements = std::variant<TextureData, TilemapData, FlagData, FlagAttribData>;
    using Parsed_Elements_Vec = std::vector<Parsed_Elements>;

    inline Parsed_Elements_Vec ParseData(const StrVec& Tokens) {
        Parsed_Elements_Vec RVec;
        auto TokenTracker = Tokens.begin();
        while (TokenTracker != Tokens.end()) {
            if (Tokens.end() - TokenTracker > 2) {
                if (TokenTracker[0] == "[" && TokenTracker[1] == "TEX" && TokenTracker[7] == "[") {
                    if (Tokens.end() - TokenTracker < 7) continue;
                    TextureData Ntex;
                    Ntex.Name = TokenTracker[2];
                    Ntex.tilewidth = std::stoi(TokenTracker[3].data());
                    Ntex.tileoffset = std::stoi(TokenTracker[4].data());
                    Ntex.Asset = std::string(TokenTracker[5].begin() + 1, TokenTracker[5].end() - 1);
                    int c = 1;
                    auto s = TokenTracker + 7;
                    for (; s < Tokens.end() && c != 0; s += 7) {
                        if (s[1] == "]") {
                            break;
                        }
                        Ntex.CoordsMap[std::stoi(s[2].data())] = {std::stoi(s[4].data()), std::stoi(s[6].data())};
                    }
                    TokenTracker = s+1;
                    RVec.push_back(Ntex);
                }
                else if (TokenTracker[0] == "[") {
                    TilemapData Map;
                    Map.Name = TokenTracker[1];
                    Map.TextureDataName = TokenTracker[2];
                    Map.w = std::stoi(TokenTracker[3].data());
                    Map.h = std::stoi(TokenTracker[4].data());
                    TokenTracker += 6;
                    auto s = TokenTracker;
                    while (s < TokenTracker + Map.w * Map.h) {
                        Map.data.emplace_back(std::stoi(s->data()));
                        s++;
                    }
                    TokenTracker = s-1;
                    RVec.push_back(Map);
                }
                else if (*TokenTracker == "DEFINE_FLAG") {
                    FlagData nflag = TokenTracker[1].data();
                    RVec.push_back(nflag);
                    TokenTracker++;
                }
                else if (*TokenTracker == "FLAG") {
                    FlagAttribData nflagdata;
                    nflagdata.TextureName = TokenTracker[1];
                    nflagdata.Flag = TokenTracker[3];
                    nflagdata.Id = std::stoi(TokenTracker[2].data());
                    RVec.push_back(nflagdata);
                    TokenTracker += 3;
                }
            }
            TokenTracker++;
        }
        return RVec;
    }

    inline void PrintData(const Parsed_Elements_Vec& v) {
        for (auto e : v) {
            if (std::holds_alternative<TextureData>(e)) {
                auto& t = std::get<TextureData>(e);
                std::cout << "TEXTURE\n" <<
                "<----------->\n" <<
                "Name : " << t.Name << " | TileWidth : " << t.tilewidth << " |  TileOffset : " << t.tileoffset
                << "\nCoords" << std::endl;
                for (auto& [k, c] : t.CoordsMap) {
                    std::cout << "Pair ID(" << k << ") : " << c.first << ", " << c.second << std::endl;
                }
                std::cout << "END\n\n";
            }
            else if (std::holds_alternative<TilemapData>(e)) {
                auto& m = std::get<TilemapData>(e);
                std::cout << "TILEMAP\n" <<
                "<----------->\n" <<
                "Name : " << m.Name << " | BaseTexture : " << m.TextureDataName << " | Width : " << m.w << " | Height : " << m.h
                << "\nCoords" << std::endl;
                for (size_t i = 0; i < m.h; i++) {
                    for (size_t c = 0; c < m.w; c++) {
                        std::cout << m.data[i * m.w + c] << ", ";
                    }
                    std::cout << std::endl;
                }
                std::cout << "End" << std::endl;
            }
            else if (std::holds_alternative<FlagData>(e)) {
                auto& f = std::get<FlagData>(e);
                std::cout << "DECLARED FLAG : " << f << std::endl;
            }
            else if (std::holds_alternative<FlagAttribData>(e)) {
                auto& f = std::get<FlagAttribData>(e);
                std::cout << "FLAG ATTRIBUTION" << std::endl << "<----------->\n" <<
                "Flag : " << f.Flag << " | ID : " << f.Id << " | Of Texture : " << f.TextureName
                << std::endl << "END" << std::endl;
            }
        }
    }

    inline std::string DumpFileContents(std::string_view file) {
        std::ifstream stream(file);
        return (std::ostringstream() << stream.rdbuf()).str();
    }
}
