package serialization;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

//When the annotation is available
@Retention(RetentionPolicy.RUNTIME)
//What is to be annotated
@Target(ElementType.FIELD)
public @interface Ignore {

}
