#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "vektorius.h"

// ============================================================
// Konstruktoriai ir destruktorius
// ============================================================

TEST_CASE("Numatytasis konstruktorius sukuria tuščią vektorių") {
    myVector<int> v;
    CHECK(v.size() == 0);
    CHECK(v.capacity() == 0);
    CHECK(v.empty() == true);
}

TEST_CASE("Konstruktorius su dydžiu sukuria vektorių su n elementų") {
    myVector<int> v(5);
    CHECK(v.size() == 5);
    CHECK(v.capacity() == 5);
    CHECK(v.empty() == false);
}

TEST_CASE("Konstruktorius su dydžiu ir pradinė reikšmė") {
    myVector<int> v(4, 7);
    REQUIRE(v.size() == 4);
    CHECK(v[0] == 7);
    CHECK(v[1] == 7);
    CHECK(v[2] == 7);
    CHECK(v[3] == 7);
}

TEST_CASE("Konstruktorius su dydžiu 0") {
    myVector<int> v(0);
    CHECK(v.size() == 0);
    CHECK(v.empty() == true);
}

// ============================================================
// Copy konstruktorius
// ============================================================

TEST_CASE("Copy konstruktorius sukuria nepriklausomą kopiją") {
    myVector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    myVector<int> v2 = v1;

    REQUIRE(v2.size() == 3);
    CHECK(v2[0] == 1);
    CHECK(v2[1] == 2);
    CHECK(v2[2] == 3);
}

TEST_CASE("Copy konstruktorius — modifikavimas nekvepia originalo") {
    myVector<int> v1;
    v1.push_back(10);
    v1.push_back(20);

    myVector<int> v2 = v1;
    v2[0] = 99;

    CHECK(v1[0] == 10); // originalas nepakitęs
    CHECK(v2[0] == 99);
}

TEST_CASE("Copy konstruktorius iš tuščio vektoriaus") {
    myVector<int> v1;
    myVector<int> v2 = v1;
    CHECK(v2.size() == 0);
    CHECK(v2.empty() == true);
}

// ============================================================
// Move konstruktorius
// ============================================================

TEST_CASE("Move konstruktorius perima duomenis") {
    myVector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    myVector<int> v2 = std::move(v1);

    REQUIRE(v2.size() == 3);
    CHECK(v2[0] == 1);
    CHECK(v2[1] == 2);
    CHECK(v2[2] == 3);
}

TEST_CASE("Move konstruktorius palieka originalą tuščią") {
    myVector<int> v1;
    v1.push_back(42);

    myVector<int> v2 = std::move(v1);

    CHECK(v1.size() == 0);
    CHECK(v1.capacity() == 0);
    CHECK(v1.empty() == true);
}

// ============================================================
// Priskyrimo operatorius
// ============================================================

TEST_CASE("Copy priskyrimas nukopijuoja elementus") {
    myVector<int> v1;
    v1.push_back(5);
    v1.push_back(10);

    myVector<int> v2;
    v2 = v1;

    REQUIRE(v2.size() == 2);
    CHECK(v2[0] == 5);
    CHECK(v2[1] == 10);
}

TEST_CASE("Copy priskyrimas — nepriklausoma kopija") {
    myVector<int> v1;
    v1.push_back(1);

    myVector<int> v2;
    v2 = v1;
    v2[0] = 999;

    CHECK(v1[0] == 1);
}

TEST_CASE("Move priskyrimas") {
    myVector<int> v1;
    v1.push_back(7);
    v1.push_back(8);

    myVector<int> v2;
    v2 = std::move(v1);

    REQUIRE(v2.size() == 2);
    CHECK(v2[0] == 7);
    CHECK(v1.empty() == true);
}

TEST_CASE("Savęs priskyrimas nekelia klaidos") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    CHECK_NOTHROW(v = v);
    REQUIRE(v.size() == 2);
    CHECK(v[0] == 1);
}

// ============================================================
// push_back
// ============================================================

TEST_CASE("push_back prideda elementus") {
    myVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    REQUIRE(v.size() == 3);
    CHECK(v[0] == 10);
    CHECK(v[1] == 20);
    CHECK(v[2] == 30);
}

TEST_CASE("push_back plečia talpą kai pilna") {
    myVector<int> v;
    CHECK(v.capacity() == 0);

    v.push_back(1);
    CHECK(v.capacity() == 1);

    v.push_back(2);
    CHECK(v.capacity() == 2);

    v.push_back(3);
    CHECK(v.capacity() == 4); // padvigubinta

    v.push_back(4);
    CHECK(v.capacity() == 4);

    v.push_back(5);
    CHECK(v.capacity() == 8); // padvigubinta
}

TEST_CASE("push_back išsaugo visus elementus po talpos plėtimo") {
    myVector<int> v;
    for (int i = 0; i < 100; i++)
        v.push_back(i);

    REQUIRE(v.size() == 100);
    for (int i = 0; i < 100; i++)
        CHECK(v[i] == i);
}

// ============================================================
// pop_back
// ============================================================

TEST_CASE("pop_back sumažina dydį") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.pop_back();
    CHECK(v.size() == 2);
    CHECK(v.back() == 2);
}

TEST_CASE("pop_back ant tuščio vektoriaus nekelia klaidos") {
    myVector<int> v;
    CHECK_NOTHROW(v.pop_back());
    CHECK(v.size() == 0);
}

// ============================================================
// insert
// ============================================================

TEST_CASE("insert įterpia elementą į vidurį") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(4);

    v.insert(v.begin() + 2, 3);

    REQUIRE(v.size() == 4);
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
    CHECK(v[2] == 3);
    CHECK(v[3] == 4);
}

TEST_CASE("insert į pradžią") {
    myVector<int> v;
    v.push_back(2);
    v.push_back(3);

    v.insert(v.begin(), 1);

    REQUIRE(v.size() == 3);
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
    CHECK(v[2] == 3);
}

TEST_CASE("insert į galą") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(2);

    v.insert(v.end(), 3);

    REQUIRE(v.size() == 3);
    CHECK(v[2] == 3);
}

TEST_CASE("insert grąžina iteratorių į įterptą elementą") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(3);

    auto it = v.insert(v.begin() + 1, 2);

    CHECK(*it == 2);
}

TEST_CASE("insert į tuščią vektorių") {
    myVector<int> v;
    v.insert(v.begin(), 42);

    REQUIRE(v.size() == 1);
    CHECK(v[0] == 42);
}

TEST_CASE("insert plečia talpą jei reikia") {
    myVector<int> v(4, 0); // size=4, capacity=4
    size_t capBefore = v.capacity();

    v.insert(v.begin() + 2, 99);

    CHECK(v.size() == 5);
    CHECK(v.capacity() > capBefore);
    CHECK(v[2] == 99);
}

// ============================================================
// erase
// ============================================================

TEST_CASE("erase pašalina elementą iš vidurio") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    v.erase(v.begin() + 1); // pašaliname '2'

    REQUIRE(v.size() == 3);
    CHECK(v[0] == 1);
    CHECK(v[1] == 3);
    CHECK(v[2] == 4);
}

TEST_CASE("erase pašalina pirmą elementą") {
    myVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    v.erase(v.begin());

    REQUIRE(v.size() == 2);
    CHECK(v[0] == 20);
    CHECK(v[1] == 30);
}

TEST_CASE("erase pašalina paskutinį elementą") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.erase(v.end() - 1);

    REQUIRE(v.size() == 2);
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
}

TEST_CASE("erase grąžina iteratorių į sekantį elementą") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    auto it = v.erase(v.begin() + 1); // triname '2'

    CHECK(*it == 3);
}

TEST_CASE("erase meta out_of_range jei pozicija už ribų") {
    myVector<int> v;
    v.push_back(1);

    CHECK_THROWS_AS(v.erase(v.end()), std::out_of_range);
    CHECK_THROWS_AS(v.erase(v.begin() - 1), std::out_of_range);
}

// ============================================================
// at
// ============================================================

TEST_CASE("at grąžina teisingą elementą") {
    myVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    CHECK(v.at(0) == 10);
    CHECK(v.at(1) == 20);
    CHECK(v.at(2) == 30);
}

TEST_CASE("at meta out_of_range už ribų") {
    myVector<int> v;
    v.push_back(1);

    CHECK_THROWS_AS(v.at(1), std::out_of_range);
    CHECK_THROWS_AS(v.at(100), std::out_of_range);
}

// ============================================================
// operator[]
// ============================================================

TEST_CASE("operator[] pasiekia elementus") {
    myVector<int> v;
    v.push_back(5);
    v.push_back(15);

    CHECK(v[0] == 5);
    CHECK(v[1] == 15);
}

TEST_CASE("operator[] leidžia modifikuoti elementą") {
    myVector<int> v;
    v.push_back(1);
    v[0] = 42;
    CHECK(v[0] == 42);
}

// ============================================================
// front ir back
// ============================================================

TEST_CASE("front grąžina pirmą elementą") {
    myVector<int> v;
    v.push_back(100);
    v.push_back(200);
    CHECK(v.front() == 100);
}

TEST_CASE("back grąžina paskutinį elementą") {
    myVector<int> v;
    v.push_back(100);
    v.push_back(200);
    CHECK(v.back() == 200);
}

// ============================================================
// clear
// ============================================================

TEST_CASE("clear pašalina visus elementus") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.clear();

    CHECK(v.size() == 0);
    CHECK(v.empty() == true);
}

TEST_CASE("clear nepakeičia talpos") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    size_t capBefore = v.capacity();

    v.clear();

    CHECK(v.capacity() == capBefore);
}

// ============================================================
// reserve
// ============================================================

TEST_CASE("reserve padidina talpą") {
    myVector<int> v;
    v.reserve(10);
    CHECK(v.capacity() == 10);
    CHECK(v.size() == 0);
}

TEST_CASE("reserve nemažina esamos talpos") {
    myVector<int> v;
    v.reserve(10);
    v.reserve(5);
    CHECK(v.capacity() == 10);
}

TEST_CASE("reserve išsaugo esamus elementus") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.reserve(100);

    CHECK(v.size() == 2);
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
}

// ============================================================
// begin / end iteratoriai
// ============================================================

TEST_CASE("begin rodo į pirmą elementą") {
    myVector<int> v;
    v.push_back(42);
    CHECK(*v.begin() == 42);
}

TEST_CASE("end rodo už paskutinio elemento") {
    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    CHECK(*(v.end() - 1) == 2);
}

TEST_CASE("range-for ciklas veikia") {
    myVector<int> v;
    for (int i = 1; i <= 5; i++)
        v.push_back(i);

    int sum = 0;
    for (int x : v)
        sum += x;

    CHECK(sum == 15);
}

// ============================================================
// size, capacity, empty
// ============================================================

TEST_CASE("size ir empty atnaujinami po push_back") {
    myVector<int> v;
    CHECK(v.empty() == true);
    v.push_back(1);
    CHECK(v.size() == 1);
    CHECK(v.empty() == false);
}

// ============================================================
// Šablono tipai
// ============================================================

TEST_CASE("myVector veikia su double tipo reikšmėmis") {
    myVector<double> v;
    v.push_back(1.1);
    v.push_back(2.2);
    CHECK(v[0] == 1.1);
    CHECK(v[1] == 2.2);
}

TEST_CASE("myVector veikia su std::string tipo reikšmėmis") {
    myVector<std::string> v;
    v.push_back("labas");
    v.push_back("pasauli");

    REQUIRE(v.size() == 2);
    CHECK(v[0] == "labas");
    CHECK(v[1] == "pasauli");
}