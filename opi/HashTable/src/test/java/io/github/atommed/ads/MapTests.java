package io.github.atommed.ads;

import com.google.common.collect.testing.MapTestSuiteBuilder;
import com.google.common.collect.testing.TestStringMapGenerator;
import com.google.common.collect.testing.features.CollectionSize;
import com.google.common.collect.testing.features.MapFeature;
import junit.framework.TestSuite;
import org.junit.runner.RunWith;
import org.junit.runners.Suite;

import java.util.Map;

/**
 * Created by gregory on 19.05.16.
 */
@RunWith(Suite.class)
@Suite.SuiteClasses(MapTests.GuavaTests.class)
public class MapTests {
    public static class GuavaTests{
        public static TestSuite suite(){
            return MapTestSuiteBuilder.using(new TestStringMapGenerator(){
                @Override
                protected Map<String, String> create(Map.Entry<String, String>[] entries) {
                    Map<String, String> map = new HashMap<>(entries.length);
                    for(Map.Entry<String , String > e: entries)
                        map.put(e.getKey(),e.getValue());
                    return map;
                }
            })
                    .named("HashMap tests")
                    .withFeatures(
                            MapFeature.ALLOWS_ANY_NULL_QUERIES,
                            MapFeature.SUPPORTS_PUT,
                            MapFeature.SUPPORTS_REMOVE,
                            CollectionSize.ANY
                    )
                    .createTestSuite();
        }
    }
}
