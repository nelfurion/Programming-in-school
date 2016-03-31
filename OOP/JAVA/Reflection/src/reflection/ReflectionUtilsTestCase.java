package reflection;
import static org.junit.Assert.*;

import java.lang.reflect.InvocationTargetException;

import org.junit.Test;

public class ReflectionUtilsTestCase {

	@Test
	public void testLoad() throws ClassNotFoundException {
		ReflectionUtils instantiator = new ReflectionUtils();
		Object loaded = instantiator.load("reflection.Student");
		assertTrue(loaded instanceof Student);
	}
	
	@Test(expected = ClassNotFoundException.class)
	public void testLoadNotExistingClass() throws ClassNotFoundException {
		ReflectionUtils instantiator = new ReflectionUtils();
		instantiator.load("com.reflection.Student");
	}

	@Test
	public void testExecuteMethod() throws ClassNotFoundException, NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {
		ReflectionUtils instantiator = new ReflectionUtils();
		Student student = new Student();
		student.setName("bojo");
		Object name = instantiator.executeMethod(student, "getName");
		assertEquals(student.getName(), name);
	}
	
	@Test
	public void testGetAllMethods() throws ClassNotFoundException {
		ReflectionUtils instantiator = new ReflectionUtils();
		String methods = instantiator.getAllMethods("reflection.Student");
		assertEquals("getNamesetName", methods);
	}
}
