.PHONY: test

test:
	rm -rf test-data/outputs/* test-data/translate-logs/* test-data/translate-error-logs/* && \
	mkdir -p test-data/outputs test-data/translate-logs test-data/translate-error-logs && \
	chmod +x run_translate.sh run_py.sh && \
	docker build -t cpp-tester . && \
	docker run --rm -v $(PWD):/app --user $(shell id -u):$(shell id -g) cpp-tester ./run_translate.sh && \
	rm -rf test-data/run-outputs/* test-data/run-error-logs/* && \
	mkdir -p test-data/run-outputs test-data/run-error-logs && \
	docker run --rm -v $(PWD):/app --user $(shell id -u):$(shell id -g) cpp-tester ./run_py.sh
