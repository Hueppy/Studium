package de.fhbielefeld.pmdungeon.performance;

import de.fhbielefeld.pmdungeon.controller.CollisionController;
import de.fhbielefeld.pmdungeon.entities.Collidable;
import de.fhbielefeld.pmdungeon.test.controller.CollisionControllerTest;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.tiles.Tile;

import java.util.GregorianCalendar;
import java.util.Random;
import java.util.function.BiConsumer;

public class CollisionControllerPerfomanceTest {
    private static class CollidableMock implements Collidable {
        private final Tile tile;

        public CollidableMock(Tile tile) {
            this.tile = tile;
        }

        @Override
        public Tile getTile() {
            return tile;
        }
    }

    private static class CallbackMock implements BiConsumer<CollidableMock, CollidableMock> {
        public int count = 0;

        @Override
        public void accept(CollidableMock collidableMock, CollidableMock collidableMock2) {
            count++;
        }
    }

    public static void main(String[] args) {
        CollisionController cc = new CollisionController();
        CallbackMock callback = new CallbackMock();

        cc.registerHandler(CollidableMock.class, CollidableMock.class, callback);

        Random r = new Random();
        for (int i = 0; i < 10000; i++) {
            Tile t = new Tile(Tile.Type.FLOOR, r.nextInt(20), r.nextInt(20));
            Collidable c = new CollidableMock(t);
            cc.registerCollidable(c);
        }

        for (int i = 0; i < 10; i++) {
            GregorianCalendar before = new GregorianCalendar();
            cc.update();
            GregorianCalendar after = new GregorianCalendar();

            double differenceInSeconds = (after.getTimeInMillis() - before.getTimeInMillis()) / 1000f;
            System.out.println(differenceInSeconds);
        }
    }
}
