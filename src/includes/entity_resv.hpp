#ifndef ENTITY_RESV
#define ENTITY_RESV
#define DEBUG
#include <algorithm>
#include <tuple>
#include <vector>
#include <utility>
#include "intalias.hpp"
#include "macros/debug.hpp"
template <typename T, typename ID = u64,
auto Sorter = []{}, auto OnUpdate = []{}>
class EntityResv {
public:
    using value_type = std::pair<ID, T>;
private:
    static constexpr bool UpdateExist = requires(T t){OnUpdate(t);};
    static constexpr bool SortExists = requires(value_type a, value_type b){{Sorter(a, b)} -> std::same_as<bool>;};
    ID counter = 1;
    std::vector<value_type> Resv;
    T& internal_getter(ID GID) {
        for (auto& e : Resv) {
            if (e.first == GID) return e.second;
        }
        DEBUG_ERROR("INVALID ACCESS AT : {}", GID);
    }
public:
    using container_type = decltype(Resv);
    ID New(auto&&... args) {
        ID nid = counter++;
        Resv.emplace_back(std::piecewise_construct,
            std::forward_as_tuple(nid),
            std::forward_as_tuple(std::forward<decltype(args)>(args)...)
        );
        return nid;
    }
    T& Get(ID GID) {
        return internal_getter(GID);
    }
    void Remove(ID RID) {
        auto iter = std::remove_if(Resv.begin(), Resv.end(), [RID](auto& p) {
            return p.first == RID;
        });
        if (iter != Resv.end())
            Resv.erase(iter);
    }
    void Update() {
        if constexpr (UpdateExist) {
            for (auto& e : Resv) {
                OnUpdate(e.second);
            }
        }
    }
    void Foreach(auto&& Functor) {
        for (auto& e : Resv) {
            Functor(e);
        }
    }
    void Sort() {
        if constexpr (SortExists) {
            std::sort(Resv.begin(), Resv.end(), Sorter);
        }
    }
    void Sort(auto&& F) {
        std::sort(Resv.begin(), Resv.end(), F);
    }
    container_type& GetContainer() {
        return Resv;
    }
    auto begin() -> decltype(Resv.begin()) {
        return Resv.begin();
    }
    auto end() -> decltype(Resv.end()) {
        return Resv.end();
    }
    bool Valid(ID GID) {
        return std::find_if(Resv.begin(), Resv.end(), [GID](auto& pred) {
            return pred.first == GID;
        }) != Resv.end();
    }
};
constexpr u8 ENTITY_RESV_NULL_ID = 0;
#endif /* ENTITY_RESV */
