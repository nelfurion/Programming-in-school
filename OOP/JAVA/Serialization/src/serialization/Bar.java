package serialization;

public class Bar {
	private String bar;
	private String foo;
	
	@Ignore
	private String fullBar;
	
	public Bar(String bar, String foo) {
		this.setFoo(foo);
		this.setBar(bar);
		this.setFullBar(bar + foo);
	}

	public String getBar() {
		return bar;
	}

	public void setBar(String bar) {
		this.bar = bar;
	}

	public String getFoo() {
		return foo;
	}

	public void setFoo(String foo) {
		this.foo = foo;
	}

	public String getFullBar() {
		return fullBar;
	}

	public void setFullBar(String fullBar) {
		this.fullBar = fullBar;
	}
	
	
}