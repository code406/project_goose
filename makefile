
SOURCE   := src/
OBJDIR   := obj/



all: goose die_test game_management_test graphic_engine_test command_test inventory_test link_test object_test player_test set_test space_test game_rules_test dialogue_test

.PHONY: all clean runv  tar goose command_test die_test game_management_test graphic_engine_test inventory_test link_test object_test player_test set_test space_test game_rules_test dialogue_test

goose:
	(cd $(SOURCE); make -f makefile_goose all)


graphic_engine_test:
	(cd $(SOURCE); make -f makefile_graphic_engine_test all)

link_test:
	(cd $(SOURCE); make -f makefile_link_test all)

object_test:
	(cd $(SOURCE); make -f makefile_object_test all)

game_management_test:
	(cd $(SOURCE); make -f makefile_game_management_test all)

command_test:
	(cd $(SOURCE); make -f makefile_command_test all)

die_test:
	(cd $(SOURCE); make -f makefile_die_test all)

inventory_test:
	(cd $(SOURCE); make -f makefile_inventory_test all)

player_test:
	(cd $(SOURCE); make -f makefile_player_test all)

set_test:
	(cd $(SOURCE); make -f makefile_set_test all)

space_test:
	(cd $(SOURCE); make -f makefile_space_test all)

game_rules_test:
	(cd $(SOURCE); make -f makefile_game_rules_test all)

dialogue_test:
	(cd $(SOURCE); make -f makefile_dialogue_test all)

clean:
	(cd $(OBJDIR); rm -f *.o)
	make cleanexe

cleanexe:
	rm -f goose die_test inventory_test player_test set_test space_test link_test object_test game_management_test command_test graphic_engine_test game_rules_test dialogue_test

cleandoc:
	rm -rf doc

tar:
	tar -czvf goose.tar.gz ./doc ./include ./obj ./src data.dat Doxyfile LEEME.txt makefile *.oca

runv:
	@echo ">>>>> Running goose with valgrind"
	valgrind --leak-check=full ./goose data.dat -l log.txt

doxygen:
	doxygen Doxyfile
