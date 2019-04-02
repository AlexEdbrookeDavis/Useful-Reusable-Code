/* ClamPizza.java
 */
 
public class ClamPizza extends Pizza
{
	public ClamPizza() {
		name = "Clam Pizza";
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";
		
		toppings.add("Clams");
	}
	public void cut() {
		System.out.println("Cutting into square slices");
	}
}