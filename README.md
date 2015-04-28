**CLAIMS** is a parallel in-memory database prototype, which runs on clusters of commodity servers and provides fast data analysis on relational dataset. 

##Highlights

### 1. ***Massively parallel execution engine***.

Loong relies on highly parallel query processing engine to dramatically accelerate data analysis speed. Query evaluations are distributed across the cluster and executed in parallel. Even if on each node which constructs a mini-network (e.g., multi-processor, multi-core, NUMA), queries are evaluated in a multi-thread fashion to leverage the computation power of multi-core hardware. 

### 2. ***Smart intra-node parallelism***. 

Pipelining the query execution among the clusters could effectively improve the query respond time but its benefits will be discounted if the workloads among execution fragments are imbalanced due to the improper intra-node parallelism. To tackle this problem, a novel elastic pipelining is proposed in CLAIMS to automatically adjust the intra-node parallelism of each query according to the runtime workload. Thanks to elastic pipelining, execution fragments which are detected to the performance bottleneck of the whole query will be given more parallelism to accelerate the data processing, while the parallelism of execution fragments that are detected to be over-producing will be decreased to avoid unnecessary computation allocation. 

![asdf](http://dase.ecnu.edu.cn/liwang/images/elastic_pipeline.jpg)

Pipelining the query execution among nodes in the cluster effectively reduces the response latency and dramatically saves storage space for intermediate query results. However, its benefits degrade tremendously when the workloads are imbalanced among execution partitions due to the improperly generated query execution plan. To tackle this problem, a novel elastic pipelining query processing model is proposed in Loong, which adapts the intra-node parallelism to the runtime workload. Beneficial from elastic pipelining query processing, the parallelism of different execution fragments in a pipelined is self-adaptive with each other and results in an optimal intra-node parallelism assignment.

### 3. ***Efficient in-memory data processing***.

Loong employs a large set of optimization techniques to achieve efficient in-memory data processing, including batch-at-a-time processing, cache-sensitive operators, SIMD-based optimization, code generation, lock-free and concurrent processing structures. These optimizations collaborate together and enable Loong to process up to gigabytes data per second within a single thread.
### 4. ***Network communication optimization***. 

Parallel query processing imposes high burdens on network communication, which becomes the performance bottleneck for in-memory parallel databases due to the relatively slow network bandwidth comparing to the efficient in-memory data processing throughput. When compiling a user query into an execution plan, Loong’s query optimizer leverages a sophisticated selectivity propagation system and cost model to generate physical query plans with minimized network communication cost. Furthermore, Loong deploys a new data exchange implementation, which offers efficient, scalable and skew-resilient network data communication among Loong instances. These optimizations greatly reduce the response time of the queries that require network data communication.

#Performance
Beneficial from the smart and massively parallelism and the in-memory data processing optimizations, CLAIMS is up to 5X faster than Shark and Impala, two state-of-the-art systems in the open source community, in the queries over TPCH dataset and Shanghai Stock Exchange dataset.

![asdf](http://dase.ecnu.edu.cn/liwang/images/compare.jpg)

##Team members
[Aoying Zhou](http://case.ecnu.edu.cn), a professor in East China Normal University, is the person in charge of this project.

[Minqi Zhou](https://github.com/polpo1980), an associate professor in East China Normal University, is the person in charge of this project.

[Li Wang](https://github.com/wangli1426), a Ph.D. student in East China Normal University, manages the master students in this team and is responsible for designing and implementing the key components of Loong, including query optimizer, catalog, physical operators, distributed communication infrastructure, storage layout, etc.

[Lei Zhang](https://github.com/egraldlo) is responsible for designing and implementing the key components of Loong, including query optimizer, physical operators, persistent data exchange, storage management, etc.

[Shaochan Dong](https://github.com/scdong) is responsible for designing and implementing in-memory index and index management, data types, as well as data loading and importing.

[Xinzhou Zhang]() is mainly responsible for web UI design and implementing data importing model.

[Zhuhe Fang](https://github.com/fzhedu) is mainly responsible for designing and implementing SQL DML parser and physical operators.

[Yu Kai](https://github.com/yukai2014) is mainly responsible for designing and implementing SQL DDL parser, catalog persistence.

[Yongfeng Li](https://github.com/NagamineLee) was a formal member of CLAIMS, who participated in designing and implementing catalog model.

[Lin Gu]() is responsible for designing the demo cases of CLAIMS.

##Publications
1. Li Wang, Minqi Zhou, Zhenjie Zhang, Yin Yang, Ming-chien Shan, Aoying Zhou. Elastic Pipelining in In-Memory Database Cluster. Submitted to SIGMOD 2015.
2. Li Wang, Minqi Zhou, Zhenjie Zhang, Ming-chien Shan, Aoying Zhou. NUMA-aware Scalable and Efficient Aggregation on Large Domains. Accepted by TKDE.
3. Li Wang, Lei Zhang, Chengcheng Yu, Aoying Zhou. Optimizing Pipelined Execution for Distributed In-memory OLAY System. In: DaMen 2014. Springer. 2014. pp. 35-56.
4. Lan Huang, Ke Xun, Xiaozhou Chen, Minqi Zhou, In-memory Cluster Computing: Interactive Data Analysis, Journal of East China Normal University, 2014
5. Shaochan Dong, Minqi Zhou, Rong Zhang，Aoying Zhou, In-Memory Index：Performance Enhancement Leveraging on Processors, Journal of East China Normal University,2014
6. Xinzhou Zhang, Minqi Zhou,A Survey of Fault Tolerance and Fault Recovery Technique in Large Distributed Parallel Computing System, Journal of East China Normal University,2014
7. Lei Zhang, Minqi Zhou, Li Wang, LCDJ: Locality Conscious Join Alogrithm for In-memory Cluster Computing, Journal of East China Normal University, 2014
8. Lei Zhang, Zhuhe Fang, Minqi Zhou，Lan Huang, Join Algorithms Towards In-memory Computing, Journal of East China Normal University, 2014
9. Yongfeng Li, Minqi Zhou, Hualiang Hu, Survey of resource uniform management and scheduling in cluster, Journal of East China Normal University, 2014

## Quick Start
Try our CLAIMS, following [Quick Start](https://github.com/dase/Claims/wiki/Quick-Start).
