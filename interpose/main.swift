//
//  main.swift
//  interpose
//
//  Created by Vitaly Khudobakhshov on 04/04/2023.
//

import Foundation

@_silgen_name("transformBlock")
func transformBlock(block: @escaping @convention(block) () -> Void, queue: DispatchQueue) -> @convention(block) () -> Void {
    let myblock = {
        print("Queue: \(queue.label)")
        block()
    }
    return myblock
}

func test() {
    let x = 10
    DispatchQueue.global().async {
        print("Captured variable is \(x)")
    }
}

install_my_hooks()

test()
sleep(1)
