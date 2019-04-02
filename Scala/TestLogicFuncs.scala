package logic
import scala.collection.mutable	


object Logicfuncs {
	def not(a: Boolean): Boolean = a match {
		case true	=> false
		case false	=> true
	}

	def and(a: Boolean, b: Boolean): Boolean = (a, b) match {
		case (true, true)	=> true
		case _				=> false
	}

	def or(a: Boolean, b: Boolean): Boolean = (a, b) match {
		case (true, _)	=> true
		case (_, true)	=> true
		case _			=> false
	}	

	def equ(a: Boolean, b: Boolean): Boolean = or(and(a, b), and(not(a), not(b)))	
	def nand(a: Boolean, b: Boolean): Boolean = not(and(a, b))
	def nor(a: Boolean, b: Boolean): Boolean  = not(or(a, b))
	def xor(a: Boolean, b: Boolean): Boolean  = not(equ(a, b))
	def impl(a: Boolean, b: Boolean): Boolean = or(not(a), b)

	def gray(n: Int): List[String] = {
		if (n == 0) List("")
		else {
			val lower = gray(n - 1)
			(lower map { "0" + _ }) ::: (lower.reverse map { "1" + _ })
		}
	}
	
	private val strings = mutable.Map(0 -> List(""))
	def grayMemoized(n: Int): List[String] = {
		if (!strings.contains(n)) {
			strings + (n -> ((grayMemoized(n - 1) map { "0" + _ }) :::
							(grayMemoized(n - 1).reverse map { "1" + _ })))
		}
		strings(n)
    }
	
}

object TestLogicFuncs {
	def main(args: Array[String]) {
		println("A     B     result")
		for {a <- List(true, false);
			b <- List(true, false)} {
			printf("%-5s %-5s %-5s\n", a, b, Logicfuncs.and(a, b))
		}
		//skip P47,48
		print(Logicfuncs.grayMemoized(3) + "\n")
		//skip P50
	}
}