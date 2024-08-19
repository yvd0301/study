// List
// Map
// Set

fun main() {

    val testList1 = listOf("a","b","c")

    println(testList1)

    println(testList1[0])

    val testList2 = mutableListOf("a","b","c")
    println("1) testList2 = $testList2")

    testList2.add("d")
    println("2) testList2 = $testList2")

    testList2.remove("a")
    println("3) testList2 = $testList2")

    // MAP
    // 5 유리
    // 10 철수
    // 15 짱구
    // 22 훈이

    val mutableList1 = mutableListOf<Int>()
    mutableList1.add(5)
    mutableList1.add(10)
    mutableList1.add(15)
    mutableList1.add(22)

    val mutableList2 = mutableListOf<String>()
    mutableList2.add("유리")
    mutableList2.add("철수")
    mutableList2.add("짱구")
    mutableList2.add("훈이")

    val findIndex = mutableList1.indexOf(10)
    println("findIndex = $findIndex")
    println("mutableList2 = " + mutableList2[findIndex])

    val testMap1 = mutableMapOf<Int, String>()
//    testMap1.add(5, "유리")
//    testMap1.add(10, "철수")
//    testMap1.add(15, "짱구")
//    testMap1.add(22, "훈이")
    testMap1.put(5, "유리")
    testMap1.put(10, "철수")
    testMap1.put(15, "짱구")
    testMap1.put(22, "훈이")

    println("testMap1[15] = " + testMap1[15])

    val testSet1 = mutableSetOf("a","b","c")
    println(testSet1)

    testSet1.add("d")
    testSet1.add("e")

    println("1) testSet1 = $testSet1")

    testSet1.add("e")
    testSet1.add("e")
    println("2) testSet1 = $testSet1")

    testSet1.remove("e")
    println("3) testSet1 = $testSet1")

}