window.BENCHMARK_DATA = {
  "lastUpdate": 1785526541582,
  "repoUrl": "https://github.com/ThePrismEngine/PrismEngine",
  "entries": {
    "ECS Benchmarks": [
      {
        "commit": {
          "author": {
            "email": "140196384+Aleksei-Kutuzov@users.noreply.github.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "5c185208bc998a5abd885b9071a015a3c6daba1f",
          "message": "Change branch reference from 'main' to 'master'",
          "timestamp": "2026-02-13T21:48:02+03:00",
          "tree_id": "38fa00d6671c657343880fe0e1f520ef2a92b5a4",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/5c185208bc998a5abd885b9071a015a3c6daba1f"
        },
        "date": 1771008564821,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.4541507758527548,
            "unit": "ns/iter",
            "extra": "iterations: 194782609\ncpu: 3.3691406197357177 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 294.2789550894636,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 304.82702253692065 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 412.83740603470534,
            "unit": "ns/iter",
            "extra": "iterations: 1824582\ncpu: 411.0530521511228 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 390.90485492253106,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 401.08816964285717 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 29.705062740926856,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 28.49469910594396 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 30.786486607143257,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 29.994419642857142 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 30.566302095684385,
            "unit": "ns/iter",
            "extra": "iterations: 24888889\ncpu: 30.7617186126709 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 31.28807392637844,
            "unit": "ns/iter",
            "extra": "iterations: 21333333\ncpu: 31.494141117095953 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 30.55351878097024,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 30.482701369149353 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 30.43327592194649,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 30.482701369149353 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 30.47686141369931,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 30.482701369149353 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 30.45118596687026,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 29.820033948080887 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 30.4531580651152,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 30.482701369149353 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 8384.600961603026,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 8370.498345989527 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 16217.238839286401,
            "unit": "ns/iter",
            "extra": "iterations: 44800\ncpu: 15694.754464285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 32513.883928572286,
            "unit": "ns/iter",
            "extra": "iterations: 22400\ncpu: 32784.59821428572 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 66772.08705356818,
            "unit": "ns/iter",
            "extra": "iterations: 8960\ncpu: 64522.87946428572 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 137992.9891522672,
            "unit": "ns/iter",
            "extra": "iterations: 4978\ncpu: 138107.67376456407 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 305235.4537743754,
            "unit": "ns/iter",
            "extra": "iterations: 2358\ncpu: 298187.0229007634 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 632672.5892857306,
            "unit": "ns/iter",
            "extra": "iterations: 1120\ncpu: 627790.1785714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 1298738.616071406,
            "unit": "ns/iter",
            "extra": "iterations: 448\ncpu: 1290457.5892857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 53.43994999999495,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 54.6875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.784457136098915,
            "unit": "ns/iter",
            "extra": "iterations: 186666667\ncpu: 3.766741064702248 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.992232142857189,
            "unit": "ns/iter",
            "extra": "iterations: 112000000\ncpu: 5.859375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 11.070748437500555,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 10.986328125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 19.175502265743894,
            "unit": "ns/iter",
            "extra": "iterations: 34461538\ncpu: 19.04296900503976 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 37.703592183863215,
            "unit": "ns/iter",
            "extra": "iterations: 18666667\ncpu: 36.8303564851722 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 75.88628348213737,
            "unit": "ns/iter",
            "extra": "iterations: 8960000\ncpu: 74.98604910714286 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 17.354450892857237,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.741071428571427 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.444481189979763,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 13.497488779029068 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "59bea5b3dab50e51dd9fed0b511451f9dfce51c3",
          "message": "Merge branch 'master' of https://github.com/Aleksei-Kutuzov/PrismEngine",
          "timestamp": "2026-02-13T22:43:22+03:00",
          "tree_id": "eb428fc94936e74af2375317d2f5709cc30bdec7",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/59bea5b3dab50e51dd9fed0b511451f9dfce51c3"
        },
        "date": 1771011887285,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.5015337437472707,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.529575886554329 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 291.60234243123335,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 285.64457588196495 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 414.6250573829893,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 371.79127804503224 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 393.8786607201499,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 446.42857142857144 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 30.19911607142894,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 29.994419642857142 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 30.84732749091839,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 31.145368790217816 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 30.769379464285407,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 30.691964285714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 30.927290178571603,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 29.296875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 30.85651365177567,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 31.145368790217816 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 30.865022321428118,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 30.691964285714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 30.848776785713994,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 30.691964285714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 31.04690178571496,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 31.389508928571427 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 30.81607503507203,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 30.482701369149353 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 8237.876116071582,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 16284.381696428492,
            "unit": "ns/iter",
            "extra": "iterations: 44800\ncpu: 16043.526785714286 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 32127.478554352045,
            "unit": "ns/iter",
            "extra": "iterations: 21333\ncpu: 32227.066047907 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 66014.6517857133,
            "unit": "ns/iter",
            "extra": "iterations: 11200\ncpu: 64174.107142857145 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 136497.85054238807,
            "unit": "ns/iter",
            "extra": "iterations: 4978\ncpu: 134968.86299718762 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 296423.3828846966,
            "unit": "ns/iter",
            "extra": "iterations: 2489\ncpu: 301325.8336681398 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 632935.3571428545,
            "unit": "ns/iter",
            "extra": "iterations: 1120\ncpu: 627790.1785714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 1285042.8571428626,
            "unit": "ns/iter",
            "extra": "iterations: 448\ncpu: 1290457.5892857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 54.82468749999977,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 55.80357142857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.466222761667462,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.452845975977061 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.419542857142697,
            "unit": "ns/iter",
            "extra": "iterations: 112000000\ncpu: 5.440848214285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 9.77195937499964,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 9.765625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 16.630244308279394,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.49693069310091 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 32.62902238482808,
            "unit": "ns/iter",
            "extra": "iterations: 21333333\ncpu: 32.95898488998414 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 62.7227767857162,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 62.779017857142854 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 17.32609569041159,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.159598367496415 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.569237662637754,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 13.497488779029068 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "0f07dd6e0a4b2ec7d113a723d93d4624b5e6638b",
          "message": "update: optimising ComponentManager class",
          "timestamp": "2026-02-14T00:04:45+03:00",
          "tree_id": "a3bdc53258df908479e63519fdf654d19dbd2bd0",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/0f07dd6e0a4b2ec7d113a723d93d4624b5e6638b"
        },
        "date": 1771016771178,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.485445261633203,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.452845975977061 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 270.31082589287377,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 313.8950892857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 306.87150107147545,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 314.9414554596024 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 307.0190300096239,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 17.06393080357138,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.741071428571427 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 19.68419294854325,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 19.182477550117337 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 16.10488627608347,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.113281142098565 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 16.506694196428537,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.694754464285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 16.9667460917403,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.49693069310091 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 16.202229838382912,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 16.32254456998864 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 16.220247767856833,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.392299107142858 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 16.091696097600455,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.113281142098565 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 16.175816632751197,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.113281142098565 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 7159.675223214558,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7149.832589285715 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 15153.542410713935,
            "unit": "ns/iter",
            "extra": "iterations: 44800\ncpu: 14648.4375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 29962.02553119331,
            "unit": "ns/iter",
            "extra": "iterations: 23579\ncpu: 29819.9669197167 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 61893.52678571427,
            "unit": "ns/iter",
            "extra": "iterations: 11200\ncpu: 61383.92857142857 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 126564.3392857133,
            "unit": "ns/iter",
            "extra": "iterations: 5600\ncpu: 128348.21428571429 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 276108.462998103,
            "unit": "ns/iter",
            "extra": "iterations: 2635\ncpu: 278700.1897533207 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 622840.4017857134,
            "unit": "ns/iter",
            "extra": "iterations: 896\ncpu: 592912.9464285715 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 1377577.5100401642,
            "unit": "ns/iter",
            "extra": "iterations: 498\ncpu: 1380522.0883534136 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 53.788071428572586,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 54.408482142857146 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.453682761689861,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.452845975977061 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.335022999999808,
            "unit": "ns/iter",
            "extra": "iterations: 100000000\ncpu: 5.3125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 9.758880760005074,
            "unit": "ns/iter",
            "extra": "iterations: 74666667\ncpu: 9.83537942037777 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 16.66008482142838,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.741071428571427 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 32.699555198431405,
            "unit": "ns/iter",
            "extra": "iterations: 21333333\ncpu: 32.95898488998414 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 62.766249999999246,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 62.779017857142854 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 19.565029556484436,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 19.566127101119683 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.970219803704177,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 13.811383866913465 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "0201e8a219447f34556c86394d0031225482a842",
          "message": "optimization: ComponentManager",
          "timestamp": "2026-02-14T13:35:11+03:00",
          "tree_id": "8a0a92253f28872d575866678e83bbcac87a51f2",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/0201e8a219447f34556c86394d0031225482a842"
        },
        "date": 1771065398532,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.513726065154049,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.529575886554329 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 275.51333146690996,
            "unit": "ns/iter",
            "extra": "iterations: 2488889\ncpu: 339.00668129434456 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 313.45383096685157,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 337.96039455180335 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 311.7346299904893,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 302.3856161779293 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 15.973872767857904,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.043526785714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 18.497413558012678,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.833705525300942 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 18.49140820081492,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 18.462956414847177,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 18.487329117273024,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.415178448112645 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 19.55559928174605,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 19.670759104203206 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 18.823454632351055,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 18.477774272122687,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 18.510021593840897,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 2692.69871627032,
            "unit": "ns/iter",
            "extra": "iterations: 263529\ncpu: 2727.4038151398895 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 5358.394642857129,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 10622.178472417767,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 10672.385391136646 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 21503.193750000093,
            "unit": "ns/iter",
            "extra": "iterations: 32000\ncpu: 20996.09375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 43399.637500002085,
            "unit": "ns/iter",
            "extra": "iterations: 16000\ncpu: 42968.75 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 95827.58805410299,
            "unit": "ns/iter",
            "extra": "iterations: 7467\ncpu: 96256.863532878 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 217251.31249999307,
            "unit": "ns/iter",
            "extra": "iterations: 3200\ncpu: 214843.75 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 506649.7999999911,
            "unit": "ns/iter",
            "extra": "iterations: 1000\ncpu: 500000 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 55.30753000000459,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 54.6875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.455360842815246,
            "unit": "ns/iter",
            "extra": "iterations: 194782609\ncpu: 3.449358253538949 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.6534529999998995,
            "unit": "ns/iter",
            "extra": "iterations: 100000000\ncpu: 5.625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 11.072984375000594,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 10.986328125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 18.826467954286766,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.79882799911499 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 37.575181471868916,
            "unit": "ns/iter",
            "extra": "iterations: 18666667\ncpu: 36.8303564851722 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 72.7742075892847,
            "unit": "ns/iter",
            "extra": "iterations: 8960000\ncpu: 69.75446428571429 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 17.282949437837026,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 17.264229795105603 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.386469642857232,
            "unit": "ns/iter",
            "extra": "iterations: 56000000\ncpu: 13.113839285714286 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "434efc314c9ec5b569f9621922b52318c111f717",
          "message": "Merge branch 'master' of https://github.com/Aleksei-Kutuzov/PrismEngine",
          "timestamp": "2026-02-14T16:22:14+03:00",
          "tree_id": "753159f546cb8bca813ab0966640dda178df9fe5",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/434efc314c9ec5b569f9621922b52318c111f717"
        },
        "date": 1771075420520,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.4801903062853405,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.376116065399793 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 272.67331249587914,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 268.5546875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 311.5440250762725,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 308.3147459069083 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 301.4333545934006,
            "unit": "ns/iter",
            "extra": "iterations: 2508800\ncpu: 305.17578125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 15.997861607143703,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.043526785714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 18.435835878892224,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 18.39105284277757,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 18.43377070030087,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 18.358182243137037,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 17.64787934610795 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 18.49336192973247,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.79882799911499 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 18.484433200754115,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 18.46349748628043,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 18.48524212933194,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 2663.3082142857183,
            "unit": "ns/iter",
            "extra": "iterations: 280000\ncpu: 2678.5714285714284 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 5351.371428571687,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 10522.301686152836,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 10672.385391136646 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 21418.547965874463,
            "unit": "ns/iter",
            "extra": "iterations: 34462\ncpu: 21763.101387034996 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 43462.01874999878,
            "unit": "ns/iter",
            "extra": "iterations: 16000\ncpu: 42968.75 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 94185.47991071336,
            "unit": "ns/iter",
            "extra": "iterations: 8960\ncpu: 94168.52678571429 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 216289.756239105,
            "unit": "ns/iter",
            "extra": "iterations: 3446\ncpu: 217643.64480557168 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 507571.1000000069,
            "unit": "ns/iter",
            "extra": "iterations: 1000\ncpu: 515625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 55.21880357143008,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 55.80357142857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.4772001723622328,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.529575886554329 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.681694642857187,
            "unit": "ns/iter",
            "extra": "iterations: 112000000\ncpu: 5.719866071428571 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 10.992374999999832,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 10.7421875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 18.854528739772686,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 37.37582611828928,
            "unit": "ns/iter",
            "extra": "iterations: 18666667\ncpu: 36.8303564851722 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 72.60850892856854,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 71.14955357142857 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 17.420095865490495,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 17.264229795105603 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.376983199210388,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 13.497488779029068 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "2f00680bcf6ffd114b674c8e1c9227429fa2ea39",
          "message": "fix: include a broken benchmarks build",
          "timestamp": "2026-04-28T22:37:25+03:00",
          "tree_id": "eadbea83f65d416fc5d40ded2646c147c7d87ce6",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/2f00680bcf6ffd114b674c8e1c9227429fa2ea39"
        },
        "date": 1777405132863,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.7960966003640872,
            "unit": "ns/iter",
            "extra": "iterations: 186666667\ncpu: 3.8504464216956316 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 272.6729137658433,
            "unit": "ns/iter",
            "extra": "iterations: 2357895\ncpu: 265.06693470235103 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 310.32060436777937,
            "unit": "ns/iter",
            "extra": "iterations: 2312258\ncpu: 283.813484481403 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 305.9700533136918,
            "unit": "ns/iter",
            "extra": "iterations: 2488889\ncpu: 345.28458279979543 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 15.68535659139241,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 15.34598204009387 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 18.436607307469657,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 18.43237784314605,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 18.461804629123233,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 30.256583305862378,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 24.69308057761679 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 20.718112684983275,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 20.08928589365434 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 20.44718124999978,
            "unit": "ns/iter",
            "extra": "iterations: 32000000\ncpu: 20.5078125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 19.474034374999505,
            "unit": "ns/iter",
            "extra": "iterations: 32000000\ncpu: 19.04296875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 19.50796856483829,
            "unit": "ns/iter",
            "extra": "iterations: 34461538\ncpu: 19.9497770528988 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 2816.449043558824,
            "unit": "ns/iter",
            "extra": "iterations: 263529\ncpu: 2786.6952024255397 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 5569.856250000172,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 11395.743769001068,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 11509.435225735599 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 21896.0468749998,
            "unit": "ns/iter",
            "extra": "iterations: 32000\ncpu: 21972.65625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 52858.517852199664,
            "unit": "ns/iter",
            "extra": "iterations: 14452\ncpu: 49733.60088569056 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 141574.12615508112,
            "unit": "ns/iter",
            "extra": "iterations: 7467\ncpu: 112997.18762555243 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 237352.55122538804,
            "unit": "ns/iter",
            "extra": "iterations: 2489\ncpu: 232271.99678585777 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 515954.821428569,
            "unit": "ns/iter",
            "extra": "iterations: 1120\ncpu: 516183.03571428574 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 54.766776785713596,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 51.61830357142857 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.482885887415086,
            "unit": "ns/iter",
            "extra": "iterations: 194782609\ncpu: 3.5295758873421805 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.361267000000112,
            "unit": "ns/iter",
            "extra": "iterations: 100000000\ncpu: 5.46875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 10.051712499999699,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 10.009765625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 16.76833113771228,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.880580244103257 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 33.278772022835234,
            "unit": "ns/iter",
            "extra": "iterations: 20363636\ncpu: 32.993862196318965 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 64.16363392857149,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 64.17410714285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 17.420221088704185,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 17.264229795105603 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.569322037636933,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 13.497488779029068 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "9f619422b74f5cd625830e004c77239e015a1f5f",
          "message": "add: new heght map\nadd: new color set material metod and new res pseudo pathes",
          "timestamp": "2026-05-14T00:23:49+03:00",
          "tree_id": "d4d9d08f56393430110accb075f96800dd03a939",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/9f619422b74f5cd625830e004c77239e015a1f5f"
        },
        "date": 1778707532365,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 2.41438727409142,
            "unit": "ns/iter",
            "extra": "iterations: 298666667\ncpu: 2.4065290151712846 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 182.37674302930887,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 204.0317852643097 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 219.3837245888291,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 244.8381587125822 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 213.93400536654596,
            "unit": "ns/iter",
            "extra": "iterations: 4072727\ncpu: 226.35325176472668 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 15.474689732139423,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.345982142857142 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 18.117018911759413,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 18.145494804871085,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 18.27195746693036,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.415178448112645 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 18.14593437499923,
            "unit": "ns/iter",
            "extra": "iterations: 32000000\ncpu: 18.06640625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 18.159872869464067,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.0315288971103 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 18.08122248287105,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 18.237503895734633,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 17.64787934610795 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 18.097636932379125,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.0315288971103 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 2634.734999999669,
            "unit": "ns/iter",
            "extra": "iterations: 280000\ncpu: 2511.160714285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 5263.958999998977,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 10448.986834881634,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 10463.12293248691 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 20904.493750002475,
            "unit": "ns/iter",
            "extra": "iterations: 32000\ncpu: 20507.8125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 42066.525448324304,
            "unit": "ns/iter",
            "extra": "iterations: 17231\ncpu: 41712.61099181708 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 92816.32516407093,
            "unit": "ns/iter",
            "extra": "iterations: 7467\ncpu: 92071.78250970939 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 199851.8862449474,
            "unit": "ns/iter",
            "extra": "iterations: 3446\ncpu: 199506.67440510736 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 437536.62500009226,
            "unit": "ns/iter",
            "extra": "iterations: 1600\ncpu: 419921.875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 67.7088124999971,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 66.96428571428571 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 2.9613873850876007,
            "unit": "ns/iter",
            "extra": "iterations: 298666667\ncpu: 2.5111607114830794 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.837902000000668,
            "unit": "ns/iter",
            "extra": "iterations: 100000000\ncpu: 5.3125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 9.373671874998633,
            "unit": "ns/iter",
            "extra": "iterations: 89600000\ncpu: 7.498604910714286 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 16.03036399093655,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 14.753069130566656 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 25.067338280948785,
            "unit": "ns/iter",
            "extra": "iterations: 24888889\ncpu: 24.483816854982962 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 48.39099275631524,
            "unit": "ns/iter",
            "extra": "iterations: 14451613\ncpu: 47.572544324290995 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 18.200757020978017,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.0315288971103 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.195944642855498,
            "unit": "ns/iter",
            "extra": "iterations: 56000000\ncpu: 13.392857142857142 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "2a8b7b7e80e57f39abaf9073c3ea668b20b6df0a",
          "message": "update: exaples code and shaders files",
          "timestamp": "2026-05-15T00:31:52+03:00",
          "tree_id": "423baded388da30332bd5e1b362b0ee11a96c6e0",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/2a8b7b7e80e57f39abaf9073c3ea668b20b6df0a"
        },
        "date": 1778794400662,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.8210523146052964,
            "unit": "ns/iter",
            "extra": "iterations: 186666667\ncpu: 3.766741064702248 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 274.29203686633474,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 272.0423985695358 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 312.8766517863519,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 306.91964285714283 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 302.29553546414263,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 266.8107961148665 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 15.600042410714362,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 14.997209821428571 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 18.437550164620532,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 18.433039450295883,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 18.475473379245326,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 18.398491235700313,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 18.455539608555522,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.79882799911499 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 18.427034093098126,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 18.45892800139119,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.415178448112645 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 18.604712375414792,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.415178448112645 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 2692.0786706585677,
            "unit": "ns/iter",
            "extra": "iterations: 263529\ncpu: 2727.4038151398895 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 5354.4285714285215,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 10567.184374999706,
            "unit": "ns/iter",
            "extra": "iterations: 64000\ncpu: 10498.046875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 21743.761244268397,
            "unit": "ns/iter",
            "extra": "iterations: 34462\ncpu: 21309.703441471767 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 43395.31730247655,
            "unit": "ns/iter",
            "extra": "iterations: 16593\ncpu: 43316.45874766468 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 94419.31163786899,
            "unit": "ns/iter",
            "extra": "iterations: 7467\ncpu: 92071.78250970939 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 217872.2129226642,
            "unit": "ns/iter",
            "extra": "iterations: 2987\ncpu: 214471.04117843992 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 497477.3999999797,
            "unit": "ns/iter",
            "extra": "iterations: 1000\ncpu: 500000 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 54.958401785718536,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 54.408482142857146 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.451162316036128,
            "unit": "ns/iter",
            "extra": "iterations: 194782609\ncpu: 3.449358253538949 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.340391999999952,
            "unit": "ns/iter",
            "extra": "iterations: 100000000\ncpu: 5.46875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 9.730471875000646,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 9.521484375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 16.728084821428116,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.741071428571427 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 32.72191457377894,
            "unit": "ns/iter",
            "extra": "iterations: 21333333\ncpu: 32.22656300354004 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 62.89682142857142,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 62.779017857142854 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 17.481894749006365,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 17.64787934610795 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.572327394766097,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 13.497488779029068 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "140196384+Aleksei-Kutuzov@users.noreply.github.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "04828839a5fabce1927bbe2cd52782abf197393e",
          "message": "Create CONTRIBUTING.md",
          "timestamp": "2026-05-20T18:18:25+03:00",
          "tree_id": "f361b960445307b0e565f85383f4c766ec15293b",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/04828839a5fabce1927bbe2cd52782abf197393e"
        },
        "date": 1779290391322,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.7953800223216354,
            "unit": "ns/iter",
            "extra": "iterations: 179200000\ncpu: 3.8364955357142856 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 275.1263426469863,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 278.6690972620133 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 312.63093947871437,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 292.96879577637435 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 304.2227919417319,
            "unit": "ns/iter",
            "extra": "iterations: 2357895\ncpu: 311.4536482752625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 16.523141630426206,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.49693069310091 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 18.80562614471901,
            "unit": "ns/iter",
            "extra": "iterations: 34461538\ncpu: 18.589564981110247 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 18.796090346393928,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.833705525300942 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 18.960680526434725,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.833705525300942 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 18.53354310535888,
            "unit": "ns/iter",
            "extra": "iterations: 34461538\ncpu: 18.136160957180728 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 19.157287671047268,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.833705525300942 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 18.99170025435358,
            "unit": "ns/iter",
            "extra": "iterations: 34461538\ncpu: 19.04296900503976 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 19.757033212117193,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 20.08928589365434 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 18.660409696471575,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.79882799911499 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 3130.2783420770284,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 3048.276213054892 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 6855.366964285586,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6277.901785714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 14071.82490256768,
            "unit": "ns/iter",
            "extra": "iterations: 49778\ncpu: 10986.279079111255 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 21991.124999999556,
            "unit": "ns/iter",
            "extra": "iterations: 32000\ncpu: 21484.375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 43341.659412040564,
            "unit": "ns/iter",
            "extra": "iterations: 14933\ncpu: 42899.95312395366 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 98912.11999463984,
            "unit": "ns/iter",
            "extra": "iterations: 7467\ncpu: 98349.4040444623 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 232938.56249999578,
            "unit": "ns/iter",
            "extra": "iterations: 3200\ncpu: 234375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 520306.89999998006,
            "unit": "ns/iter",
            "extra": "iterations: 1000\ncpu: 515625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 58.21369999999888,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 57.8125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.477968699146588,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.376116065399793 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.334689000000026,
            "unit": "ns/iter",
            "extra": "iterations: 100000000\ncpu: 5.3125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 9.761906206419807,
            "unit": "ns/iter",
            "extra": "iterations: 74666667\ncpu: 9.83537942037777 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 16.740298325399177,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.49693069310091 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 34.188162664074305,
            "unit": "ns/iter",
            "extra": "iterations: 20363636\ncpu: 34.528460438008224 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 62.924660714287484,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 64.17410714285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 17.427574883297375,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 17.264229795105603 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.694536546006239,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 13.811383866913465 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "c37d0825bbe68bab148dc9792dd2211a8a4b4cbd",
          "message": "fix: benchmarks 2",
          "timestamp": "2026-07-10T00:50:34+03:00",
          "tree_id": "8b3dd9e81c313bf6b226f584ee259e019d8d06c6",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/c37d0825bbe68bab148dc9792dd2211a8a4b4cbd"
        },
        "date": 1783633960215,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.880725528783918,
            "unit": "ns/iter",
            "extra": "iterations: 186666667\ncpu: 3.8504464216956316 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 276.25620538905036,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 244.140625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 318.9892857602672,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 390.625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 307.35932003682274,
            "unit": "ns/iter",
            "extra": "iterations: 2280727\ncpu: 294.5880852903482 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 15.992386160712208,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.043526785714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 15.896946428572027,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.694754464285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 15.668968749998108,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.694754464285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 16.178095982140356,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.043526785714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 16.28312276785948,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.392299107142858 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 15.779401680048606,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 14.962332489091523 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 16.318016185367423,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.113281142098565 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 15.1985947785536,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 15.066964420240753 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 15.257395089288854,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.345982142857142 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 2144.9455189127666,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2131.0012622781946 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 4351.760000000127,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 8543.160714286863,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8544.921875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 17192.120706167745,
            "unit": "ns/iter",
            "extra": "iterations: 40727\ncpu: 16497.041274829964 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 34618.72421920925,
            "unit": "ns/iter",
            "extra": "iterations: 20364\ncpu: 34527.84325279906 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 78870.9933035798,
            "unit": "ns/iter",
            "extra": "iterations: 8960\ncpu: 80217.63392857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 187830.53844093787,
            "unit": "ns/iter",
            "extra": "iterations: 3733\ncpu: 188353.87088132868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 430485.49999994633,
            "unit": "ns/iter",
            "extra": "iterations: 1600\ncpu: 429687.5 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 62.24300999999741,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 62.5 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.4446902617055097,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.452845975977061 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.795028000000002,
            "unit": "ns/iter",
            "extra": "iterations: 100000000\ncpu: 5.78125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 10.817135937500668,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 10.498046875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 18.820374275179333,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.833705525300942 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 37.34790287490067,
            "unit": "ns/iter",
            "extra": "iterations: 19478261\ncpu: 36.900111360043894 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 72.87695535712909,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 71.14955357142857 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 16.709591517860236,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.741071428571427 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 11.9531535714259,
            "unit": "ns/iter",
            "extra": "iterations: 56000000\ncpu: 11.997767857142858 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "c6383af99b9a57880ad9c955a2544d26afb20edd",
          "message": "change: TextureStorage теперь использует IdPool template",
          "timestamp": "2026-07-10T15:03:32+03:00",
          "tree_id": "cd79ac91d02065a5ee63d63e373616600f49f7ab",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/c6383af99b9a57880ad9c955a2544d26afb20edd"
        },
        "date": 1783685144612,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.9606472259541716,
            "unit": "ns/iter",
            "extra": "iterations: 194782609\ncpu: 3.9306640563583373 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 272.17357909560604,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 318.53236606116707,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 313.8950892857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 306.39325253889103,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 320.1730053648663 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 15.677912946426682,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.694754464285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 15.699263392855908,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 14.997209821428571 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 15.787589285715901,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.694754464285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 15.599591517856076,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.345982142857142 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 15.379993303571586,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.345982142857142 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 15.146526785717436,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.345982142857142 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 15.17982366071432,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 14.997209821428571 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 15.54675863595038,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 15.694754394219846 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 15.286700892858105,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.345982142857142 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 2141.0562500001615,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2148.4375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 4234.2881766575,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 8361.169642857443,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8370.535714285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 17219.561961350202,
            "unit": "ns/iter",
            "extra": "iterations: 40727\ncpu: 16497.041274829964 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 35089.88901984071,
            "unit": "ns/iter",
            "extra": "iterations: 20364\ncpu: 35295.12865841681 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 79834.17410713907,
            "unit": "ns/iter",
            "extra": "iterations: 8960\ncpu: 80217.63392857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 183398.47307799343,
            "unit": "ns/iter",
            "extra": "iterations: 3733\ncpu: 179982.58773104742 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 435653.1645569209,
            "unit": "ns/iter",
            "extra": "iterations: 1659\ncpu: 423824.5931283906 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 57.94158035714402,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 57.198660714285715 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.453291868833175,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.452845975977061 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.657103000000916,
            "unit": "ns/iter",
            "extra": "iterations: 100000000\ncpu: 5.78125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 11.083807142857234,
            "unit": "ns/iter",
            "extra": "iterations: 56000000\ncpu: 10.881696428571429 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 18.8821823114493,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.833705525300942 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 37.441376311777454,
            "unit": "ns/iter",
            "extra": "iterations: 19478261\ncpu: 37.70228769395789 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 72.47211607142795,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 72.54464285714286 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 16.644640624998072,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.392299107142858 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 11.970628124998939,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 11.962890625 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "175fba2227388e95f502657ad6cb9b94ffaea579",
          "message": "update: cmakelists for PrismEngine lib project",
          "timestamp": "2026-07-31T22:26:46+03:00",
          "tree_id": "10147f5953e5cbbb5c05848f394f8e1cd85cd920",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/175fba2227388e95f502657ad6cb9b94ffaea579"
        },
        "date": 1785526537872,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.797538743218759,
            "unit": "ns/iter",
            "extra": "iterations: 186666667\ncpu: 3.766741064702248 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 277.2770628522124,
            "unit": "ns/iter",
            "extra": "iterations: 2357895\ncpu: 318.0803216428212 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 321.80484430506755,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 299.24659834882175 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 315.5760954229653,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 283.90061894631805 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 15.708209821429111,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.694754464285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 15.593968749999679,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.694754464285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 15.644636160714954,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.694754464285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 15.317299107142953,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 14.997209821428571 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 15.238792410715414,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 14.6484375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 15.374573368862709,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 15.066964218451053 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 15.265229910714138,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 14.997209821428571 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 15.359725377859197,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 15.38085930633545 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 15.337267857142526,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.345982142857142 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 2151.0231249999733,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2148.4375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 4304.444374999861,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 8359.95553591291,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 8370.498345989527 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 17180.271073243355,
            "unit": "ns/iter",
            "extra": "iterations: 40727\ncpu: 17264.345520170893 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 35115.73570181846,
            "unit": "ns/iter",
            "extra": "iterations: 19478\ncpu: 34494.044563096824 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 79780.85937499886,
            "unit": "ns/iter",
            "extra": "iterations: 8960\ncpu: 78473.77232142857 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 190500.80364318285,
            "unit": "ns/iter",
            "extra": "iterations: 3733\ncpu: 188353.87088132868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 434455.0000000069,
            "unit": "ns/iter",
            "extra": "iterations: 1600\ncpu: 439453.125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 57.11445535714026,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 57.198660714285715 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.519874279428893,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.529575886554329 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.676872321428915,
            "unit": "ns/iter",
            "extra": "iterations: 112000000\ncpu: 5.580357142857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 11.007879687499944,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 10.986328125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 18.9649206319321,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.415178448112645 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 37.34920647590588,
            "unit": "ns/iter",
            "extra": "iterations: 18666667\ncpu: 37.66741004165339 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 72.60373883928624,
            "unit": "ns/iter",
            "extra": "iterations: 8960000\ncpu: 71.49832589285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 16.444828014878734,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.49693069310091 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 11.992598214286584,
            "unit": "ns/iter",
            "extra": "iterations: 56000000\ncpu: 11.997767857142858 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}