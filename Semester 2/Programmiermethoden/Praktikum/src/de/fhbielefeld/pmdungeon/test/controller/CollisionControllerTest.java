package de.fhbielefeld.pmdungeon.test.controller;

import de.fhbielefeld.pmdungeon.controller.CollisionController;
import de.fhbielefeld.pmdungeon.entities.Collidable;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.tiles.Tile;
import java.util.function.BiConsumer;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

/** Test für den CollisionController. */
public class CollisionControllerTest {
  private CollisionController sut;

  @Before
  public void setUp() {
    sut = new CollisionController();
  }

  @Test
  public void testTwoCollidingExpectCallbackCalledTwice() {
    CallbackMock callback = new CallbackMock();

    sut.registerHandler(CollidableMock.class, CollidableMock.class, callback);

    Tile t = new Tile(Tile.Type.FLOOR, 0, 0);
    Collidable a = new CollidableMock(t);
    Collidable b = new CollidableMock(t);

    sut.registerCollidable(a);
    sut.registerCollidable(b);

    sut.update();

    Assert.assertEquals(2, callback.count);
  }

  @Test
  public void testTwoNotCollidingExpectCallbackNotCalled() {
    CallbackMock callback = new CallbackMock();

    sut.registerHandler(CollidableMock.class, CollidableMock.class, callback);

    Tile ta = new Tile(Tile.Type.FLOOR, 0, 0);
    Tile tb = new Tile(Tile.Type.FLOOR, 0, 1);
    Collidable a = new CollidableMock(ta);
    Collidable b = new CollidableMock(tb);

    sut.registerCollidable(a);
    sut.registerCollidable(b);

    sut.update();

    Assert.assertEquals(0, callback.count);
  }

  private class CollidableMock implements Collidable {
    private final Tile tile;

    public CollidableMock(Tile tile) {
      this.tile = tile;
    }

    @Override
    public Tile getTile() {
      return tile;
    }
  }

  private class CallbackMock implements BiConsumer<CollidableMock, CollidableMock> {
    public int count = 0;

    @Override
    public void accept(CollidableMock collidableMock, CollidableMock collidableMock2) {
      count++;
    }
  }
}
