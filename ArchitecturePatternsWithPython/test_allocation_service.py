import datetime as dt

import pytest

from allocation_service import Batch, OrderLine, OutOfStock, allocate

today = dt.date.today()
tomorrow = today + dt.timedelta(1)
later = tomorrow + dt.timedelta(10)


def make_batch_and_line(
    sku: str, batch_qty: int, line_qty: int
) -> tuple[Batch, OrderLine]:
    return (
        Batch("batch-001", sku, batch_qty, eta=dt.date.today()),
        OrderLine("order-123", sku, line_qty),
    )


def test_allocating_to_a_batch_reduces_the_available_quantity():
    batch = Batch("batch-001", "SMALL-TABLE", qty=20, eta=dt.date.today())
    line = OrderLine("order-ref", "SMALL-TABLE", 2)

    batch.allocate(line)

    assert batch.available_quantity == 18


def test_can_allocate_if_available_greater_than_required():
    large_batch, small_line = make_batch_and_line("ELEGANT-LAMP", 20, 2)
    assert large_batch.can_allocate(small_line)


def test_cannot_allocate_if_available_smaller_than_required():
    small_batch, large_line = make_batch_and_line("ELEGANT-LAMP", 2, 20)
    assert small_batch.can_allocate(large_line) is False


def test_can_allocate_if_available_equal_to_required():
    batch, line = make_batch_and_line("ELEGANT-LAMP", 2, 2)
    assert batch.can_allocate(line)


def test_cannot_allocate_if_skus_do_not_match():
    batch = Batch("batch-001", "UNCOMGORTABLE-CHAIR", 100, eta=None)
    line = OrderLine("order-ref", "EXPENSIVE-TOASTER", 10)

    assert batch.can_allocate(line) is False


def test_can_deallocate_unallocated_lines():
    batch, unallocated_line = make_batch_and_line("DECORATIVE-TRINKET", 20, 2)
    batch.deallocate(unallocated_line)

    assert batch.available_quantity == 20


def test_allocation_is_idempotent():
    batch, line = make_batch_and_line("ANGULAR-DESK", 20, 2)

    batch.allocate(line)
    batch.allocate(line)

    assert batch.available_quantity == 18


def test_prefers_current_stock_batches_to_shipment():
    in_stock_batch = Batch("in-stock-batch", "RETRO-CLOCK", 100, eta=None)
    shipment_batch = Batch("shipment-batch", "RETRO-CLOCK", 100, eta=tomorrow)
    line = OrderLine("oref", "RETRO-CLOCK", 10)

    allocate(line, [in_stock_batch, shipment_batch])

    assert in_stock_batch.available_quantity == 90
    assert shipment_batch.available_quantity == 100


def test_prefers_earlier_batches():
    earliest = Batch("speedy-batch", "RETRO-CLOCK", 100, eta=today)
    medium = Batch("normal-batch", "RETRO-CLOCK", 100, eta=tomorrow)
    latest = Batch("slow-batch", "RETRO-CLOCK", 100, eta=later)
    line = OrderLine("oref", "RETRO-CLOCK", 10)

    allocate(line, [earliest, medium, latest])

    assert earliest.available_quantity == 90
    assert medium.available_quantity == 100
    assert latest.available_quantity == 100


def test_returns_allocated_vatch_ref():
    in_stock_batch = Batch("in-stock-batch", "RETRO-CLOCK", 100, eta=None)
    shipment_batch = Batch("shipment-batch", "RETRO-CLOCK", 100, eta=tomorrow)
    line = OrderLine("oref", "RETRO-CLOCK", 10)

    allocation = allocate(line, [in_stock_batch, shipment_batch])

    assert allocation == in_stock_batch.reference


def test_raises_out_of_stock_exception_if_cannot_allocate():
    batch = Batch("batch1", "SMALL-FORK", 10, eta=today)
    allocate(OrderLine("order1", "SMALL-FORK", 10), [batch])

    with pytest.raises(OutOfStock, match="SMALL-FORK"):
        allocate(OrderLine("order2", "SMALL-FORK", 1), [batch])
