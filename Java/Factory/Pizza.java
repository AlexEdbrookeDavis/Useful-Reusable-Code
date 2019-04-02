/* Pizza.java
 */

import java.util.*; 

 
public abstract class Pizza
{
	String name;
	String dough;
	String sauce;
	ArrayList<String> toppings = new ArrayList<String>();
	
	public void prepare() {
		System.out.println("Preparing " + name);
		System.out.println("Tossing Dough");
		System.out.println("Adding Sauce");
		System.out.println("Adding Toppings");
		for(int i = 0; i < toppings.size(); i++) {
			System.out.println("    " + toppings.get(i));
		}

	}
	
	public void bake() {
		System.out.println("Baking for 25 minutes at 350");
	}
	
	public void cut() {
		System.out.println("Cutting into diagonal slices");
	}
	
	public void box() {
		System.out.println("Place pizza into box");		
	}
}