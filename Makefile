default:
	gcc -o witchertracker src/main.c src/utils.c src/type_detections.c src/sentence_handle.c src/question_handle.c src/capacity_ensuring.c

grade:
	python3 test/grader.py ./witchertracker test-cases