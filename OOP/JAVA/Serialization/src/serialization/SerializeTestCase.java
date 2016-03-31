package serialization;

import static org.junit.Assert.*;

import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;

import org.junit.Test;

public class SerializeTestCase {
	
	@Test
	public void testCheckFields() {
		Class<Bar> aClass = Bar.class;
		Field[] fields = aClass.getFields();
		System.out.println("fields: " + fields.length);
		
		fields = aClass.getDeclaredFields();
		System.out.println("declared fields fields: " + fields.length);
	}
	
	@Test
	public void testFieldValues() {
		Bar bar = new Bar("ala", "bala");
		Class<Bar> aClass = Bar.class;
		Field[] fields = aClass.getDeclaredFields();
		
		for(Field field: fields) {
			System.out.println(field.getName());
			field.setAccessible(true);
			try {
				System.out.println(field.get(bar));
			} catch (IllegalArgumentException | IllegalAccessException e) {
				e.printStackTrace();
			}
		}
	}
	
	@Test
	public void testSerializeInitial() throws IllegalArgumentException, IllegalAccessException {
		Bar bar = new Bar("ala", "bala");
		Class<Bar> aClass = Bar.class;
		Field[] fields = aClass.getDeclaredFields();
		List<String> result = new ArrayList<String>();
		
		for(Field field: fields) {
			StringBuffer buffer = new StringBuffer();
			field.setAccessible(true);
			buffer.append(field.getName());
			buffer.append(": ");
			Object val = field.get(bar);
			buffer.append("\"");
			buffer.append(val.toString());
			buffer.append("\"");
			System.out.println(buffer.toString());
			result.add(buffer.toString());
		}
		
		StringBuffer buffer = new StringBuffer();
		buffer.append("{");
		buffer.append(String.join(",", result));
		buffer.append("}");
		System.out.println(buffer.toString());
	}
	
	@Test
	public void testAnnotationIgnore() {
		Bar bar = new Bar("ala", "bala");
		Class<Bar> aClass = Bar.class;
		Field[] fields = aClass.getDeclaredFields();
		for(Field field: fields) {
			Annotation ignore = field.getAnnotation(Ignore.class);
			if (ignore != null) {
				System.out.println("name: " + field.getName() + " ignore");
			} else {
				
			}
		}
	}
}
