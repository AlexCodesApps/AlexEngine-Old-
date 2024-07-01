#include "metatile.hpp"

int main() {
    auto str = MetaTile::DumpFileContents("world1.mt");
    auto tokens = MetaTile::Tokenizer(str);
    auto code = MetaTile::StripComments(tokens);
    auto data = MetaTile::ParseData(code);
    MetaTile::PrintData(data);
}
