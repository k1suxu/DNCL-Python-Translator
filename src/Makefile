.PHONY: test
# Dockerイメージをビルドし、テストを実行
test:
	mkdir -p test-data/outputs && \
	mkdir -p test-data/log && \
	docker build -t cpp-tester . && \
	docker run --rm -v $(PWD):/app --user $(shell id -u):$(shell id -g) cpp-tester ./run_test.sh
