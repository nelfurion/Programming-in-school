package reflection;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class ReflectionUtils {
	public Object load(String name) throws ClassNotFoundException {
		Class<?> cls = Class.forName(name);
		
		try {
			return cls.newInstance();
		} catch (InstantiationException | IllegalAccessException e) {
			e.printStackTrace();
		}
		
		return null;
	}
	
	public Object executeMethod(Object obj, String methodName) throws NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {
		Class<? extends Object> cls = obj.getClass();
		Method method = cls.getMethod(methodName);
		Object result = method.invoke(obj);
		return result;
	}
	
	public String getAllMethods(String name) throws ClassNotFoundException {
		Class<?> cls = Class.forName(name);
		Method[] methods = cls.getDeclaredMethods();
		
		String result = "";
		for(Method method: methods) {
			result += method.getName();
		}
		
		return result;
	}
	
	public String serialize(Object object) {
		Class<?extends Object> cls =  object.getClass();
		String result = "";
		result += cls.getSimpleName() + "[";
		
		List<Field> fields = new ArrayList<>();
		for (Field field : cls.getFields()) {
			field.setAccessible(true);
			try {
				Object obj = field.get(object);
				result += field.getName() + "=" + obj.toString() + ",";
			} catch (IllegalArgumentException | IllegalAccessException e) {
				e.printStackTrace();
			}
		}
		
		result.substring(0, result.length() - 1);
		result += "]";
		
		return result;
	}
}
