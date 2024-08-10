fun main() {
    val testList1 = ArrayList<String>()

    testList1.add("a")
    testList1.add("b")
    testList1.add("c")

    println("testList1 = $testList1")
    println("testList1[0] = " + testList1[0])

    val testList2 = listOf("a","b","c")
    println("testList2 = " + testList2)

    val testList3 = mutableListOf<String>("a","b","c")
    println("testList3 = " + testList3)

    testList3.add("d")
    println("testList3 = " + testList3)


    val testList4 = listOf("student1", "student2", "student3", "student4", "teacher1", "student5")
    println("testList4 = " + testList4)

    println( "testList4.filter = " + testList4.filter { it.startsWith("s") } )


    val testList5 = listOf("student1", "student2", "student3", "student4", "teacher1", "student5", null)

//    println("testList5.filter = " + testList5.filter{it.startsWith("s") } )
    println("testList5.filter = " + testList5.filterNotNull().filter{ it.startsWith("s") } )

    var test1 : String = "a"
    var test2 : String = "b"

    test1 = test2

    println("test1 = " + test1)

    var test3 : String = "c"
    var test4 : String? = "d"   // ? 는 null 일수도있는값

    //test3 = test4 // ->Kotlin: Type mismatch: inferred type is String? but String was expected

    test3 = test4!!
    println("test3 = " + test3)

    val testList6 = listOf("a","b","c","d","e","f")
    for(i in testList6){
        println("i = " + i)
    }

    for( j in 1..10){
        println("j = " + j)
    }

    for(z in 1..10 step 2){
        println("z = " + z)
    }

    for(k in 1..3){
        println("k의 값은 " + k)
    }

    for(y in 1..3){
        println("y의 값은 $y")
    }

    for(i in 1..3){
        for(j in 1..3){
            println("is is $i j is $j")
            
        }
    }

}