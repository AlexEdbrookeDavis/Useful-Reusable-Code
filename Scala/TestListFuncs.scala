object Listfuncs {
	def lastRec[A](ls: List[A]): A = ls match {
		case x :: Nil  => x
		case _ :: tail => lastRec(tail)
		case _         => throw new NoSuchElementException
	}
	
	def secondLastRec[A](ls: List[A]): A = ls match {
		case x :: _ :: Nil  => x
		case _ :: tail => secondLastRec(tail)
		case _         => throw new NoSuchElementException
	}
	
	def distRec[A](ls: List[A], dist: Int): A = (ls, dist) match {
		case (Nil, _)       => throw new NoSuchElementException
		case (x :: tail, 0) => x
		case (_ :: tail, y) => distRec(tail, y - 1)
		case _              => throw new NoSuchElementException
	}
	
	def len[A](ls: List[A]): Int = {
		def lenRec(ls: List[A], len: Int): Int = ls match {
			case x :: Nil       => len + 1
			case _ :: tail      => lenRec(tail, 1 + len)
			case _              => throw new NoSuchElementException		
		}
		lenRec(ls, 0)
	}

	def reverseRec[A](ls: List[A]): List[A] = ls match {
		case Nil  => Nil
		case head :: tail => reverseRec(tail) ::: List(head)
		case _         => throw new NoSuchElementException
	}
	
	def paliTest[A](ls: List[A]): Boolean = (reverseRec(ls) == ls)
	
	def flattenRec(ls: List[Any]): List[Any] = ls flatMap { //apply flatMap to the given recursive function
		case x: List[_]  => flattenRec(x)                  //If an element of the list is a list, apply flatten to the inside of it
		case y           => List(y)                        //Else, make it a list to be flattened
	}
	
	def compressRec[A](ls: List[A]): List[A] = ls match {
		case Nil            => Nil
		case x :: Nil       => x :: Nil
		case x :: y :: tail => if (x == y) compressRec(y :: tail) else x :: compressRec(y :: tail)
		case _              => throw new NoSuchElementException
	}
	
	//TODO; PACK P09
	
	def duplicate[A](ls: List[A]): List[A] = ls flatMap {
		x => List(x, x)
	}
	
	def duplicateN[A](ls: List[A], count: Int): List[A] = ls flatMap {
		x => List.fill(count)(x)
	}
	
	def delN[A](ls: List[A], len: Int): List[A] = {
		def delNRec(ls: List[A], len: Int, oldLen: Int): List[A] = (ls, len, oldLen) match {
			case (Nil, _, _) 		=> Nil
			case (x :: tail, 0, y)	=> delNRec(tail, y, y)
			case (x :: tail, y, z) => x :: delNRec(tail, y - 1, z)
			case _              => throw new NoSuchElementException		
		}
		delNRec(ls, len, len)
	}
	
	def splitRec[A](ls: List[A], len: Int): (List[A], List[A]) = (ls, len) match {
		case (Nil, _) 		=> (Nil, Nil)
		case (x, 0)			=> (Nil, x)
		case (x :: tail, y) => {
				val (pre, post) = splitRec(tail, y - 1)
				(x :: pre, post)
			}
		case _              => throw new NoSuchElementException		
	}

	def sliceRec[A](ls: List[A], start: Int, end: Int): List[A] = (ls, start, end) match {
		case (Nil, _, _) 		=> Nil
		case (_, 0, 0)			=> Nil
		case (x :: tail, 0, z)	=> x :: sliceRec(tail, 0, z - 1)
		case (x :: tail, y, z)	=> sliceRec(tail, y - 1, z - 1)
		case _              	=> throw new NoSuchElementException		
	}		
	
	def rotate[A](n: Int, ls: List[A]): List[A] = {
		val nBounded = if (ls.isEmpty) 0 else n % ls.length
		if (nBounded < 0) rotate(nBounded + ls.length, ls)
		else (ls drop nBounded) ::: (ls take nBounded)
	}
	
	def removeRec[A](ls: List[A], dist: Int): List[A] = (ls, dist) match {
		case (Nil, _)       => throw new NoSuchElementException
		case (x :: tail, 0) => tail
		case (x :: tail, y) => x :: removeRec(tail, y - 1)
		case _              => throw new NoSuchElementException
	}
	
	def insertRec[A](ls: List[A], dist: Int, data: A): List[A] = (ls, dist, data) match {
		case (Nil, _, _)       => throw new NoSuchElementException
		case (x :: tail, 0, z) => x :: z :: tail
		case (x :: tail, y, z) => x :: insertRec(tail, y - 1, z)
		case _              => throw new NoSuchElementException
	}
	
	def range(start: Int, end: Int): List[Int] = {
		def rangeRec(cur: Int, end: Int): List[Int] = {
			if (cur < end) (cur :: rangeRec(cur + 1, end))
			else List(cur)
		}
		rangeRec(start, end)
	}
	
	//TODO; P23

}

object TestListFuncs {
	def main(args: Array[String]) {
		val list: List[Int] = List(1, 2, 3)
		print(Listfuncs.lastRec(list))
		print(Listfuncs.secondLastRec(list))
		print(Listfuncs.distRec(list, 2))
		print(Listfuncs.len(list) + "\n")
		print(Listfuncs.reverseRec(list) + "\n")
		print(Listfuncs.paliTest(list) + "\n")
		val listlist: List[Any] = List(List(1), 2, 3)
		print(Listfuncs.flattenRec(listlist) + "\n")
		val listrep: List[Int] = List(1, 1, 3)
		print(Listfuncs.compressRec(listrep) + "\n")
		//TODO: P09, P10, P11, P12, P13
		print(Listfuncs.duplicate(list) + "\n")
		print(Listfuncs.duplicateN(list, 4) + "\n")
		print(Listfuncs.delN(Listfuncs.duplicateN(list, 4), 2) + "\n")
		print(Listfuncs.splitRec(Listfuncs.duplicateN(list, 4), 2) + "\n")
		print(Listfuncs.sliceRec(Listfuncs.duplicateN(list, 4), 2, 5) + "\n")
		print(Listfuncs.rotate(2, Listfuncs.duplicateN(list, 4)) + "\n")
		print(Listfuncs.removeRec(list, 1) + "\n")
		print(Listfuncs.insertRec(list, 1, 4) + "\n")
		print(Listfuncs.range(5, 9) + "\n")
		//TODO; P23 - 28

	}
}